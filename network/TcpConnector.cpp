#include "TcpConnector.h"
#include "TcpConnection.h"
#include "EventDispatcher.h"

namespace network
{
	CTcpConnector::CTcpConnector(const CAddress& address, CEventDispatcher* eventDispatcher):
		CEventHandler(EHandler_TcpConnector, nullptr, eventDispatcher),
		_state(EDisconnected),
		_address(address)
	{

	}

	CTcpConnector::~CTcpConnector()
	{

	}

	int32 CTcpConnector::connect()
	{
		assert(_endPoint == nullptr);
		SOCKET socket = createSocket(EPROTO_TCP);
		_endPoint = CObjectPool<CEndPoint>::Instance()->createUnique(socket, _address);
		bool code = _endPoint->connect();
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
		//setState(ECONNECT_CON);
		//CConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(_endPoint);
		//_netWork->onNewConnection(connection);
	}

	void CTcpConnector::retry()
	{
		_endPoint.reset();

	}
}