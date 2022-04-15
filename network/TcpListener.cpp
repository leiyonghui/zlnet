#include "TcpListener.h"
#include "TcpConnection.h"

namespace network
{
	CTcpListener::CTcpListener(CEndPointUnPtr&& endPoint, CEventDispatcher* eventDispatcher) :
		CListener(EHandlerTcpListener, std::forward<CEndPointUnPtr>(endPoint), eventDispatcher)
	{

	}

	bool CTcpListener::listen()
	{
		if (!_endpoint->good())
			return false;
		if (_endpoint->bind())
			return false;
		if (!_endpoint->listen())
		{
			_eventDispatcher->registerInputHandler(_endpoint->getSocket(), this);
			return true;
		}
		return false;
	}

	int32 CTcpListener::handleInputEvent()
	{
		CEndPointUnPtr endPoint = _endpoint->accept();
		if (endPoint == nullptr)
			return -1;
		CTcpConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(EHandlerTcpConnection, std::move(endPoint));
		connection->setEventDispatcher(_eventDispatcher);
		_eventDispatcher->registerInputHandler(connection->getSocket(), connection.get());
		if (_newConnectionCallback)
		{
			_newConnectionCallback(std::static_pointer_cast<CConnection>(connection));
		}
		return 0;
	}

	int32 CTcpListener::handleErrorEvent(int32 ev)
	{
		if (_disListenCallback)
		{
			_disListenCallback(_endpoint->getAddress());
		}
		return 0;
	}
}
