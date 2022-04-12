#include "EpollerEvent.h"
#include "EventDispatcher.h"
#include "EventHandlers.h"

namespace network
{
	CEventDispatcher::CEventDispatcher(IScheduler *scheduler):TimerHander(scheduler),_eventPoller(new CEpollerEvent())
	{

	}

	CEventDispatcher::~CEventDispatcher()
	{
		delete _eventPoller;
	}

	void CEventDispatcher::registerInputHandler(SOCKET socket, CEventHandler* handler)
	{
		_eventPoller->registerInputHandler(socket, handler);
	}

	void CEventDispatcher::deregisterInputHandler(SOCKET socket, CEventHandler* handler)
	{
		_eventPoller->deregisterInputHandler(socket, handler);
	}

	void CEventDispatcher::registerWriteHandler(SOCKET socket, CEventHandler* handler)
	{
		_eventPoller->registerWriteHandler(socket, handler);
	}

	void CEventDispatcher::deregisterWriteHandler(SOCKET socket, CEventHandler* handler)
	{
		_eventPoller->deregisterWriteHandler(socket, handler);
	}

	void CEventDispatcher::deregisterHandler(SOCKET socket)
	{
		_eventPoller->deregisterHandler(socket);
	}

	void CEventDispatcher::process(uint32 milli)
	{
		_eventPoller->poll(milli);
	}
}