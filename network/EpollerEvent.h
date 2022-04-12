#pragma once
#ifdef __linux
#include "Configs.h"
#include "EventPoller.h"

namespace network
{
#define EPOLL_EIZE 3000

	class CEpollerEvent : public CEventPoller
	{
	public:
		CEpollerEvent();

		virtual~CEpollerEvent();

		virtual void poll(int32 milli) override;

		virtual void registerInputHandler(SOCKET socket, CEventHandler* handler) override;

		virtual void deregisterInputHandler(SOCKET socket, CEventHandler* handler) override;

		virtual void registerWriteHandler(SOCKET socket, CEventHandler* handler) override;

		virtual void deregisterWriteHandler(SOCKET socket, CEventHandler* handler) override;

		virtual void deregisterHandler(SOCKET socket) override;

	protected:

		void updateHandler(SOCKET socket, CEventHandler* handler, int32 events);

		int32 _epfd;
		struct epoll_event* _events;
	};
}

#endif // __liunx


