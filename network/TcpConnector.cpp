#include "TcpConnector.h"
#include "TcpConnection.h"
#include "EventDispatcher.h"

namespace network
{
	CTcpConnector::CTcpConnector(const CAddress& address, CEventDispatcher* eventDispatcher):
		CEventHandler(EHandlerTcpConnector, nullptr, eventDispatcher),
		_retryCount(0),
		_maxRetry(3),
		_retryId(0),
		_state(EDisconnected),
		_address(address),
		_newCallback(nullptr)
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
		case EISCONN:
			connecting();
			return 0;

		case EAGAIN:
		case EADDRINUSE:
		case EADDRNOTAVAIL:
		case ECONNREFUSED:
		case ENETUNREACH:
			retry();
			return -1;

		case EACCES:
		case EPERM:
		case EAFNOSUPPORT:
		case EALREADY:
		case EBADF:
		case EFAULT:
		case ENOTSOCK:
			core_log_error("connect error");
			_endpoint.reset();
			return -1;

		default:
			core_log_error("connect Unexpected error");
			_endpoint.reset();
			return -1;
		}
		return 0;
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
			retry();
		}
		else
		{
			onConnected();
			return 0;
		}
		return -1;
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

	void CTcpConnector::onDisConnect()
	{

	}

	void CTcpConnector::retry()
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
			onDisConnect();
		}
	}
}