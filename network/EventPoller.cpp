#include "EventPoller.h"

namespace network
{
	CEventPoller::~CEventPoller()
	{
	}

	void CEventPoller::registerHandler(SOCKET socket, CEventHandler* handler)
	{
		auto iter = _handlers.find(socket);
		if (iter != _handlers.end())
		{
			assert(iter->second == handler);
		}
		else
		{
			 _handlers[socket] = handler;
		}
	}

	void CEventPoller::deregisterHandler(SOCKET socket)
	{
		assert(_handlers.erase(socket));
	}

	bool CEventPoller::hasHandler(CEventHandler *handler)
	{
		auto socket = handler->getSocket();
		auto iter = _handlers.find(socket);
		return iter != _handlers.end() && iter->second == handler;
	}

}