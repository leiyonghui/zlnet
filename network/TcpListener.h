#pragma once
#include "Listener.h"

namespace network
{
	class CTcpListener : public CListener
	{
	public:
		CTcpListener(CEndPointUnPtr&& endPoint, CEventDispatcher* eventDispatcher);
		virtual ~CTcpListener() = default;

		virtual bool listen() override;
		virtual int32 handleInputEvent() override;
		virtual int32 handleWriteEvent() override { return 0; };
		virtual int32 handleErrorEvent(int32 ev) override;
	};
	typedef std::shared_ptr<CTcpListener> CTcpListenerPtr;
}