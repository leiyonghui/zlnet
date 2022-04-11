#include "Timers.h"

namespace core
{
	namespace timerset
	{
		class TimerSet : public IScheduler
		{
		public:
			TimerSet();

			virtual ~TimerSet();

			virtual Tick tick() override;

			virtual void update(Tick now) override;

			virtual void addTimer(TimerEvent* event) override;

			virtual void delTimer(TimerEvent* event) override;

		protected:
			TimerSetImpl* _timer;
		};

		class TimerSetImpl
		{
			friend class TimerSet;
		protected:
			TimerSetImpl() :_curTick(0) {}

			void _update(Tick now);

			void _addTimer(TimerEvent* event);

			void _delTimer(TimerEvent* event);

		private:
			std::map<Tick, TimerSlot*> _queue;
			Tick _curTick;
		};
	}
}
