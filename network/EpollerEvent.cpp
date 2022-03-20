#ifdef __linux

#include <sys/epoll.h>
#include <unistd.h>
#include "EpollerEvent.h"
#include "Configs.h"

namespace network
{
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
			//CEventHandler* handler = (CEventHandler*)event.data.ptr;
			SOCKET socket = event.data.u32;
			auto iter = _handlers.find(socket);
			if (iter == _handlers.end())
			{
				assert(false);
				continue;
			}
			const uint16& ev = event.events;
			if (ev & (EPOLLERR | EPOLLHUP) && !(ev & EPOLLIN))
			{
				iter->second->handleErrorEvent(ev);
			}
			else
			{
				if (ev & EPOLLIN)
				{
					iter->second->handleInputEvent();
				}
				if (ev & EPOLLOUT)
				{
					iter = _handlers.find(socket);
					if (iter != _handlers.end())
					{
						iter->second->handleWriteEvent();
					}
					else
					{
						core_log_warning("epoll null handler", socket);
					}
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

	void CEpollerEvent::updateHandler(SOCKET socket, CEventHandler* handler, uint32 ev)
	{
		handler->updateEvent(ev);
		epoll_event event;
		event.events = ev;
		event.data.u32 = socket;
		auto iter = _handlers.find(socket);
		if (iter != _handlers.end())
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
				core_log_error("epoll mod error", errno);
				return;
			}
			registerHandler(socket, handler);
		}
	}
}


#endif // __linux

