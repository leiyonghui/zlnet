#include "TcpListener.h"
#include "TcpConnection.h"

namespace network
{
	CTcpListener::CTcpListener(CEndPointUnPtr&& endPoint, CEventDispatcher* eventDispatcher) :
		CListener(EHandler_TcpListener, std::forward<CEndPointUnPtr>(endPoint), eventDispatcher)
	{
		_eventDispatcher->registerInputHandler(_endpoint->getSocket(), this);
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
		CEndPointUnPtr endPoint = _endpoint->accept();
		if (endPoint == nullptr)
			return -1;
		CTcpConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(std::move(endPoint));
		if (_newConnectionCallback)
		{
			_newConnectionCallback(connection);
		}
		return 0;
	}
}
