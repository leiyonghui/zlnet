#include "Listener.h"

namespace network
{
	CListener::CListener(const CEndPointPtr endpoint, onNewConnectionCallback&& connectionCallback):
		_endpoint(endpoint),
		_connectionCallback(std::move(connectionCallback))
	{

	}

	CListener::~CListener()
	{

	}

	void CListener::listen()
	{
	}

}
