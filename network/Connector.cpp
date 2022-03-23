#include "Connector.h"
#include "TcpConnection.h"

namespace network
{
	CConnector::CConnector(CEndPointPtr endPoint, CNetWork* network):
		_state(ECONNECT_NONE),
		_endPoint(endPoint),
		_netWork(network),
		_retryClock(0),
		_retryTime(0)
	{

	}

	CConnector::~CConnector()
	{

	}

	int32 CConnector::connect()
	{
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
		_retryClock = TimeHelp::clock_ms().count() + 2000 * ++_retryTime;
		setState(ECONNECT_DIS);
		return 1;
	}

	void CConnector::onConnected()
	{
		_retryTime = 0;
		setState(ECONNECT_CON);
		CConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(_endPoint);
		_netWork->onNewConnection(connection);
	}
}