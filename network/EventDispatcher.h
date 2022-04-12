#pragma once
#include "Configs.h"

namespace network
{
	class CEventHandler;
	class CEventDispatcher : public TimerHander
	{
	public:
		CEventDispatcher(IScheduler* scheduler);

		virtual ~CEventDispatcher();

		virtual void registerInputHandler(SOCKET socket, CEventHandler* handler);

		virtual void deregisterInputHandler(SOCKET socket, CEventHandler* handler);

		virtual void registerWriteHandler(SOCKET socket, CEventHandler* handler);

		virtual void deregisterWriteHandler(SOCKET socket, CEventHandler* handler);

		virtual void deregisterHandler(SOCKET socket);

		void process(uint32 milli);

	protected:
		class CEventPoller* _eventPoller;
	};
}