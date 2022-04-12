#ifdef __linux

#include <sys/epoll.h>
#include <unistd.h>
#include "EpollerEvent.h"
#include "Configs.h"

namespace network
{
	void printfEvent(int32 fd, int32 ev)
	{
		std::ostringstream oss;
		oss << "fd:" << fd << " ";
		if (ev & EPOLLIN)
			oss << "IN ";
		if (ev & EPOLLPRI)
			oss << "PRI ";
		if (ev & EPOLLOUT)
			oss << "OUT ";
		if (ev & EPOLLHUP)
			oss << "HUP ";
		if (ev & EPOLLRDHUP)
			oss << "RDHUP ";
		if (ev & EPOLLERR)
			oss << "ERR ";
		//if (ev & EPOLLNVAL)
		//	oss << "NVAL ";
		std::string str = oss.str();
		printf("%s\n", str.c_str());
	}

	CEpollerEvent::CEpollerEvent() :_epfd(epoll_create(EPOLL_EIZE)), _events(new epoll_event[EPOLL_EIZE])
	{

	}

	CEpollerEvent::~CEpollerEvent()
	{
		::close(_epfd);
		delete _events;
	}

	void CEpollerEvent::poll(int32 milli)
	{
		int32 cnt = ::epoll_wait(_epfd, _events, EPOLL_EIZE, milli);
		for (int32 i = 0; i < cnt; i++)
		{
			const epoll_event& event = _events[i];
			CEventHandler* handler = (CEventHandler*)event.data.ptr;
			const uint32& ev = event.events;
			int32 events = handler->getEvent();
			printfEvent(handler->getSocket(), ev);
			if (ev & (EPOLLERR | EPOLLHUP) && !(ev & EPOLLIN))
			{
				handler->handleErrorEvent(ev);
			}
			else
			{
				if (ev & EPOLLIN)
				{
					if (events & ev)
						handler->handleInputEvent();
				}
				if (ev & EPOLLOUT)
				{
					if (events & ev)
						handler->handleWriteEvent();
				}
			}			
		}
	}

	void CEpollerEvent::registerInputHandler(SOCKET socket, CEventHandler* handler)
	{
		updateHandler(socket, handler, handler->getEvent() | EPOLLIN);
	}

	void CEpollerEvent::deregisterInputHandler(SOCKET socket, CEventHandler* handler)
	{
		updateHandler(socket, handler, handler->getEvent() ^ EPOLLIN);
	}

	void CEpollerEvent::registerWriteHandler(SOCKET socket, CEventHandler* handler)
	{
		updateHandler(socket, handler, handler->getEvent() | EPOLLOUT);
	}

	void CEpollerEvent::deregisterWriteHandler(SOCKET socket, CEventHandler* handler)
	{
		updateHandler(socket, handler, handler->getEvent() ^ EPOLLOUT);
	}

	void CEpollerEvent::deregisterHandler(SOCKET socket)
	{
		auto iter = _handlers.find(socket);
		if (iter == _handlers.end())
			return;
		if (::epoll_ctl(_epfd, EPOLL_CTL_DEL, socket, NULL))
		{
			core_log_error("epoll del", errno);
			return;
		}
		iter->second->updateEvent(0);
		CEventPoller::deregisterHandler(socket);
	}

	void CEpollerEvent::updateHandler(SOCKET socket, CEventHandler* handler, int32 events)
	{
		epoll_event event;
		event.events = events;
		event.data.ptr = handler;
		if (hasHandler(handler))
		{
			if (::epoll_ctl(_epfd, EPOLL_CTL_MOD, socket, &event))
			{
				core_log_error("epoll mod error", errno);
				return;
			}
		}
		else
		{
			if (::epoll_ctl(_epfd, EPOLL_CTL_ADD, socket, &event) < 0)
			{
				core_log_error("epoll add error", errno);
				return;
			}
			registerHandler(socket, handler);
		}
		handler->updateEvent(events);
	}
}

#endif // __linux

