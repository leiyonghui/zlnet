#include "TcpConnection.h"

namespace network
{
	void CTcpConnection::onAwake(CEndPointPtr endpoint)
	{
		CConnection::onAwake(endpoint);
	}

	void CTcpConnection::onRecycle()
	{
		CConnection::onRecycle();
	}

	int32 CTcpConnection::handleInputEvent()
	{
		return int32(0);
	}

	int32 CTcpConnection::handleWriteEvent()
	{
		return int32(0);
	}

	int32 CTcpConnection::handleErrorEvent(uint32 ev)
	{
		return int32(0);
	}
}