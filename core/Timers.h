#pragma once
#include "FastNode.h"
#include "Configs.h"

namespace core
{
	using Tick = uint64;

	typedef std::function<void()> TimeoutCallback;

	namespace timerwheel {
		class TimerWheel;
	};
	class IScheduler;
	class TimerHander;
	class TimerEvent;

	class TimerEvent : CFastNode<core::TimerEvent*>
	{
		friend class IScheduler;
		friend class TimerHander;
		friend class timerwheel::TimerWheel;

		int64 _id;
		TimerHander* _hander;
		Tick _tick;
		Tick _period;
		int32 _count;
		TimeoutCallback _callback;
		bool _invalid;
	public:
		TimerEvent(int64 id, TimerHander* ptr, Tick tick, Tick period, int32 count, TimeoutCallback&& callback) :
			CFastNode<TimerEvent*>(this),
			_id(id),
			_hander(ptr),
			_tick(tick),
			_period(period),
			_count(count),
			_callback(std::move(callback)),
			_invalid(true)
		{
			//assert(_hander);
		}

		~TimerEvent();

		void onTimeout()
		{
			if (_callback)
				_callback();
		}

		Tick tick()
		{
			return _tick;
		}
	};

	class TimerHander
	{
		friend class TimerEvent;
		friend class timerwheel::TimerWheel;

		using Duration = std::chrono::milliseconds;
		using Datetime = std::chrono::system_clock::time_point;

		int64 _nextId;
		std::map<int64, TimerEvent*> _timerMap;
		IScheduler* _scheduler;

		TimerHander(const TimerHander&) = delete;
		TimerHander operator=(const TimerHander&) = delete;
	public:
		TimerHander(IScheduler* IScheduler) : _nextId(0), _scheduler(IScheduler) {}

		virtual ~TimerHander()
		{
			cancel();
		}

		int64 addTimer(Tick delay, Tick duration, int32 count, TimeoutCallback&& callback);

		int64 addTimer(Duration delay, Duration duration, int32 count, TimeoutCallback&& callback);

		int64 addTimer(Datetime time, Duration duration, int32 count, TimeoutCallback&& callback);

		bool cancel(int64 id);

		void cancel();

		int64 nextId()
		{
			while (++_nextId)
			{
				if (_nextId && (int)_timerMap.count(_nextId) == 0)
				{
					return _nextId;
				}
			}
			return 0;
		}
	};


	class IScheduler//implement timerwheel or heap
	{
	public:
		IScheduler() {}

		virtual Tick tick() = 0;

		virtual void update(Tick now) = 0;

		virtual void addTimer(TimerEvent* event) = 0;

		virtual void delTimer(TimerEvent* event) = 0;
	};
}