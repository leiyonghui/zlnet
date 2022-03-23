#include "TcpListener.h"
#include "TcpConnection.h"

namespace network
{
	CTcpListener::CTcpListener(CEndPointPtr endPoint, CNetWork* network):
		CListener(endPoint, network)
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
		if (_network)
		{
			_network->onNewConnection(connection);
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
