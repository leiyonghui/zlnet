#include "Connector.h"
#include "TcpConnection.h"

namespace network
{
	CConnector::CConnector(CEndPointPtr endPoint, CNetWork* network):
		_state(ECONNECT_NONE),
		_endPoint(endPoint),
		_netWork(network)
	{

	}

	CConnector::~CConnector()
	{

	}

	void CConnector::connect()
	{
		bool code = _endPoint->connect();
		if (code == 0)
		{
			onConnected();
			return;
		}
		core_log_error(code, strerror(code));
		switch (code)
		{
		case EINPROGRESS:// The socket is nonblocking and the connection cannot be completed immediately.
			retry();
			break;
		default:
		{
			_netWork->removeConnector(_endPoint->getAddress());
			break;
		}
		}
	}

	void CConnector::onConnected()
	{
		setState(ECONNECT_CON);
		CConnectionPtr connection = CObjectPool<CTcpConnection>::Instance()->create(_endPoint);
		_netWork->onNewConnection(connection);
	}

	void CConnector::retry()
	{
		setState(ECONNECT_DIS);
	}
}