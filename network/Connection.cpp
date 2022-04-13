#include "Connection.h"
#include "Endpoint.h"
#include "Network.h"

namespace network
{
    CConnection::CConnection(EHandlerType type) : CEventHandler(type), _state(EDisconnected)
    {
    }

	void CConnection::onAwake(EHandlerType type, CEndPointUnPtr&& endPoint)
	{
		_type = type;
		_endpoint = std::move(endPoint);
	}

	void CConnection::onRecycle()
	{
		assert(_state == EDisconnected);
		_event = 0;
		_endpoint.reset();
	}
}