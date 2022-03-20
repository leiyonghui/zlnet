#include "Connection.h"
#include "Endpoint.h"

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
}