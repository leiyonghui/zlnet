#include "Connection.h"
#include "Endpoint.h"
#include "Network.h"

namespace network
{
	CConnection::~CConnection()
	{

	}

	void CConnection::onAwake(EHandlerType type, CEndPointUnPtr&& endPoint)
	{
		_type = type;
		_endpoint = std::move(endPoint);
	}

	void CConnection::onRecycle()
	{
		_type = EHandler_None;
		_event = 0;
		_endpoint.reset();
		_network = nullptr;
		assert(_state == EDisconnected);
	}
}