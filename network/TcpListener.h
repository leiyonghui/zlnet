#pragma once
#include "Listener.h"

namespace network
{
	class CTcpListener : public CListener
	{
	public:
		CTcpListener() = default;

		CTcpListener(CEndPointPtr endPoint, onNewConnectionCallback&& connectionCallback);

		virtual void listen() override;

		virtual int32 handleInputEvent() override;

		virtual int32 handleWriteEvent() override;

		virtual int32 handleErrorEvent(uint32 ev) override;
	};
	typedef std::shared_ptr<CTcpListener> CTcpListenerPtr;
}