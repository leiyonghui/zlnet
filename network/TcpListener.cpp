#include "TcpListener.h"
#include "TcpConnection.h"

namespace network
{
	CTcpListener::CTcpListener(CEndPointPtr endPoint, onNewConnectionCallback&& connectionCallback):
		CListener(endPoint, std::forward<onNewConnectionCallback>(connectionCallback))
	{

	}

	bool CTcpListener::listen()
	{
		if (!_endpoint->good())
			return false;
		if (_endpoint->bind())
			return false;
		return _endpoint->listen() == 0;
	}

	int32 CTcpListener::handleInputEvent()
	{
		CEndPointPtr endPoint = _endpoint->accept();
		if (endPoint == nullptr)
			return -1;
		CTcpConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(endPoint);
		if (_connectionCallback)
		{
			_connectionCallback(std::static_pointer_cast<CConnection>(connection));
		}
		return 0;
	}

	int32 CTcpListener::handleWriteEvent()
	{
		return int32(0);
	}

	int32 CTcpListener::handleErrorEvent(uint32 ev)
	{
		return int32(0);
	}
}
