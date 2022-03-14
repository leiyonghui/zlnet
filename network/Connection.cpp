#include "Connection.h"
#include "Endpoint.h"

namespace network
{
	CConnection::CConnection(CEndPoint* endPoint): _endPoint(endPoint)
	{

	}

	CConnection::~CConnection()
	{
		delete _endPoint;
	}
}