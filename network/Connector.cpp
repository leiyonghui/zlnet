#include "Connector.h"
#include "TcpConnection.h"

namespace network
{
	CConnector::CConnector(CEndPointUnPtr&& endPoint, CNetWork* network):
		_state(ECONNECT_NONE),
		_endPoint(std::move(endPoint)),
		_netWork(network)
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
		setState(ECONNECT_DIS);
		return 1;
	}

	void CConnector::onConnected()
	{
		setState(ECONNECT_CON);
		CConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(_endPoint);
		_netWork->onNewConnection(connection);
	}
}