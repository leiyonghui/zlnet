#include "Connection.h"
#include "Endpoint.h"
#include "Network.h"

namespace network
{
	void CConnection::onAwake(CEndPointPtr endPoint)
	{
		_endPoint = endPoint;
	}
	
	void CConnection::onRecycle()
	{

	}

	CConnection::~CConnection()
	{
		
	}

	void CConnection::setNetWork(CNetWork* network)
	{
		_network = network;
	}
}