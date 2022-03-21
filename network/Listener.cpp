#include "Listener.h"

namespace network
{
	CListener::CListener(const CEndPointPtr endpoint, onNewConnectionCallback&& connectionCallback):
		_endpoint(endpoint),
		_connectionCallback(std::move(connectionCallback))
	{
		_endpoint->setReuseAddr(true);
	}

	CListener::~CListener()
	{

	}
}
