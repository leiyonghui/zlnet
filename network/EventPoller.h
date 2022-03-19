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

	protected:
		std::map<SOCKET, CEventHandler*> _handlers;
	};
}