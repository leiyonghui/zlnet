#include "TcpListener.h"

namespace network
{
	CTcpListener::CTcpListener(CEndPointPtr endPoint):IListener(endPoint)
	{

	}

	void CTcpListener::listen()
	{
		if (!_endpoint->good())
			return;
		if (_endpoint->bind() < 0)
			return;
		_endpoint->listen();
	}

	int32 CTcpListener::handInputEvent()
	{
		return int32();
	}

	int32 CTcpListener::handWriteEvent()
	{
		return int32();
	}

	int32 CTcpListener::handErrorEvent()
	{
		return int32();
	}
}
