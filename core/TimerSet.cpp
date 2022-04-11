#include "TimerSet.h"

namespace core
{
	namespace timerset
	{
		TimerSet::TimerSet():_timer(new TimerSetImpl()) {

		}

		TimerSet::~TimerSet()
		{
			delete _timer;
		}

		Tick TimerSet::tick()
		{
			return _timer->_curTick;
		}

		void TimerSet::update(Tick now)
		{
			_timer->_update(now);
		}

		void TimerSet::addTimer(TimerEvent* event)
		{
			_timer->_addTimer(event);
		}

		void TimerSet::delTimer(TimerEvent* event)
		{
			_timer->_delTimer(event);
		}

		void TimerSetImpl::_update(Tick now)
		{

		}

		void TimerSetImpl::_addTimer(TimerEvent* event)
		{
			auto tick = event->tick();
			auto iter = _queue.find(tick);
			if (iter == _queue.end())
			{
				iter = _queue.insert({ tick, new TimerSlot() }).first;
			}
			iter->second->_slot.pushBack(*event);
		}

		void TimerSetImpl::_delTimer(TimerEvent* event)
		{
			delete event;
		}
		

	}
}