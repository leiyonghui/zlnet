#pragma once
#include "Listener.h"

namespace network
{
	class CTcpListener : public IListener
	{
	public:
		CTcpListener() = default;

		CTcpListener(CEndPointPtr endPoint);

		virtual void listen() override;

		virtual int32 handInputEvent() override;

		virtual int32 handWriteEvent() override;

		virtual int32 handErrorEvent() override;
	};
}