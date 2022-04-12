#include "Listener.h"

namespace network
{
	CListener::CListener(EHandlerType type, CEndPointUnPtr&& endpoint, CEventDispatcher* eventDispatcher):
		CEventHandler(type, std::forward<CEndPointUnPtr>(endpoint), eventDispatcher),_newConnectionCallback(nullptr)
	{
		_endpoint->setReuseAddr(true);
	}

	CListener::~CListener()
	{

	}
}
