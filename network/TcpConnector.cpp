#include "TcpConnector.h"
#include "TcpConnection.h"
#include "EventDispatcher.h"

namespace network
{
	CTcpConnector::CTcpConnector(const CAddress& address, CEventDispatcher* eventDispatcher):
		CEventHandler(EHandler_TcpConnector, nullptr, eventDispatcher),
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
		assert(_endPoint == nullptr);
		SOCKET socket = createSocket(EPROTO_TCP);
		_endPoint = CObjectPool<CEndPoint>::Instance()->createUnique(socket, _address);
		int32 code = _endPoint->connect();
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
			_endPoint.reset();
			return -1;

		default:
			core_log_error("connect Unexpected error");
			_endPoint.reset();
			return -1;
		}
		return 0;
	}

	int32 CTcpConnector::handleWriteEvent()
	{
		assert(_state == EConnecting);
		assert(_endPoint);
		_eventDispatcher->deregisterHandler(_endPoint->getSocket());
		auto err = _endPoint->getSocketError();
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
		assert(_endPoint);
		setState(EConnecting);
		_eventDispatcher->deregisterHandler(_endPoint->getSocket());
		_eventDispatcher->registerWriteHandler(_endPoint->getSocket(), this);
	}

	void CTcpConnector::onConnected()
	{
		setState(EConnected);
		CTcpConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(EHandler_TcpConnection, std::move(_endPoint));
		_eventDispatcher->registerInputHandler(connection->getSocket(), connection.get());
		if (_newCallback)
		{
			_newCallback(std::static_pointer_cast<CConnection>(connection));
		}
		assert(_endPoint == nullptr);
	}

	void CTcpConnector::onDisConnect()
	{

	}

	void CTcpConnector::retry()
	{
		assert(_state == EDisconnected);
		_endPoint.reset();
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