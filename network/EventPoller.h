#pragma once
#include "Configs.h"
#include "EventHandlers.h"

namespace network
{
	class CEventPoller
	{
	public:
		CEventPoller() = default;

		virtual void poll(int32 milli) = 0;

		virtual void registerHandler(SOCKET socket, CEventHandler* handler);

		virtual void deregisterHandler(SOCKET socket);

		virtual void registerInputHandler(SOCKET socket, CEventHandler* handler) = 0;

		virtual void deregisterInputHandler(SOCKET socket, CEventHandler* handler) = 0;

		virtual void registerWriteHandler(SOCKET socket, CEventHandler* handler) = 0;

		virtual void deregisterWriteHandler(SOCKET socket, CEventHandler* handler) = 0;

	protected:
		std::map<SOCKET, CEventHandler*> _handlers;
	};
}