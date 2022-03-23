#include "Listener.h"

namespace network
{
	CListener::CListener(const CEndPointPtr endpoint, CNetWork* network):
		_endpoint(endpoint),
		_network(network)
	{
		_endpoint->setReuseAddr(true);
	}

	CListener::~CListener()
	{

	}
}
