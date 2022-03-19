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

	int32 CConnection::handInputEvent()
	{
		return int32();
	}

	int32 CConnection::handWriteEvent()
	{
		return int32();
	}

	int32 CConnection::handErrorEvent()
	{
		return int32();
	}
}