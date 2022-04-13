#include "Connection.h"
#include "Endpoint.h"
#include "Network.h"

namespace network
{
    CConnection::CConnection(EHandlerType type) : CEventHandler(type), _state(EDisconnected)
    {
    }
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
		_type = EHandlerNone;
		_event = 0;
		_endpoint.reset();
		assert(_state == EDisconnected);
	}
}