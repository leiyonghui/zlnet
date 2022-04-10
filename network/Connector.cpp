#include "Connector.h"
#include "TcpConnection.h"
#include "EventDispatcher.h"

namespace network
{
	CConnector::CConnector(const CAddress& address, CEventDispatcher* eventDispatcher):
		_state(EDisconnected),
		_address(address),
		_eventDispatcher(eventDispatcher),
		_endPoint(nullptr)
	{

	}

	CConnector::~CConnector()
	{

	}

	int32 CConnector::connect()
	{
		setState(EConnecting);
		bool code = _endPoint->connect();
		if (code == 0)
		{
			onConnected();
			return 0;
		}
		core_log_error(code, strerror(code));
		switch (code)
		{
		case EINPROGRESS:// The socket is nonblocking and the connection cannot be completed immediately.
			break;
		default:
			return -1;
		}
		setState(EDisconnected);
		return 1;
	}

	void CConnector::connecting()
	{

	}

	void CConnector::onConnected()
	{
		//setState(ECONNECT_CON);
		//CConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(_endPoint);
		//_netWork->onNewConnection(connection);
	}
}