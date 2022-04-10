#pragma once
#include "Listener.h"

namespace network
{
	class CTcpListener : public CListener
	{
	public:
		CTcpListener() = default;

		CTcpListener(CEndPointUnPtr&& endPoint, CEventDispatcher* eventDispatcher);

		virtual bool listen() override;

		virtual int32 handleInputEvent() override;
	};
	typedef std::shared_ptr<CTcpListener> CTcpListenerPtr;
}