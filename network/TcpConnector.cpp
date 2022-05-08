#include "TcpConnector.h"
#include "TcpConnection.h"
#include "EventDispatcher.h"

namespace network
{
	CTcpConnector::CTcpConnector(const CAddress& address, CEventDispatcher* eventDispatcher):
		CEventHandler(EHandlerTcpConnector, nullptr, eventDispatcher),
		_retryCount(0),
		_maxRetry(5),
		_retryId(0),
		_state(EDisconnected),
		_address(address),
		_newCallback(nullptr),
		_timeoutCallback(nullptr)
	{

	}

	CTcpConnector::~CTcpConnector()
	{
		if (_retryId)
			_eventDispatcher->cancel(_retryId);
	}

	int32 CTcpConnector::connect()
	{
		assert(_endpoint == nullptr);
		SOCKET socket = createSocket(EPROTO_TCP);
		_endpoint = CObjectPool<CEndPoint>::Instance()->createUnique(socket, _address);
		int32 code = _endpoint->connect();
		switch (code)
		{
		case 0:
		case EINPROGRESS:
		case EINTR:
		case EISCONN:		//The socket is already connected
			connecting();
			return 0;

		case EAGAIN:		//the socket is nonblocking, and the connection cannot be completed immediately.For other socket families, there are insufficient entries in the routing cache.
		case EADDRINUSE:	//Local address is already in use.
		case EADDRNOTAVAIL:	//Cannot assign requested address 
		case ECONNREFUSED:	//响应RST,没有进程等待与之连接//没有人在侦听远程地址
		case ENETUNREACH:	//Network is unreachable.
			reConnect();
			return -1;

		case EACCES:
		case EPERM:
		case EAFNOSUPPORT:
		case EALREADY:
		case EBADF:
		case EFAULT:
		case ENOTSOCK:
			core_log_error("connect error", code);
		default:
			core_log_error("connect Unexpected error", code);
		}
		_endpoint.reset();
		return -1;
	}

	int32 CTcpConnector::handleWriteEvent()
	{
		assert(_state == EConnecting);
		assert(_endpoint);
		_eventDispatcher->deregisterHandler(_endpoint->getSocket());
		auto err = _endpoint->getSocketError();
		if (err)
		{
			core_log_error("connector handle error", strerror(err));
			reConnect();
		}
		else
		{
			onConnected();
			return 0;
		}
		return -1;
	}

	int32 CTcpConnector::handleErrorEvent(int32 ev)
	{
		assert(_state == EConnecting);
		if (_state == EConnecting)
		{
			assert(_endpoint);
			_eventDispatcher->deregisterHandler(_endpoint->getSocket());
			reConnect();
		}
	}

	void CTcpConnector::connecting()
	{
		assert(_endpoint);
		setState(EConnecting);
		_eventDispatcher->deregisterHandler(_endpoint->getSocket());
		_eventDispatcher->registerWriteHandler(_endpoint->getSocket(), this);
	}

	void CTcpConnector::onConnected()
	{
		setState(EConnected);
		CTcpConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(EHandlerTcpConnection, std::move(_endpoint));
		connection->setEventDispatcher(_eventDispatcher);
		_eventDispatcher->registerInputHandler(connection->getSocket(), connection.get());
		if (_newCallback)
		{
			_newCallback(std::static_pointer_cast<CConnection>(connection));
		}
		assert(_endpoint == nullptr);
	}

	void CTcpConnector::reConnect()
	{
		assert(_state == EDisconnected);
		_endpoint.reset();
		_retryCount++;
		if (_retryCount <= _maxRetry)
		{
			_retryId = _eventDispatcher->addTimer(std::chrono::milliseconds(_retryCount * 2000), 0ms, [this]() {
				connect();
			});
		}
		else
		{
			if (_timeoutCallback)
			{
				_timeoutCallback(_address);
			}
		}
	}
}