#pragma once
#include "Connection.h"

namespace network
{
	class CTcpConnection : 
		public CConnection
	{
	public:
		void onAwake(CEndPointPtr endpoint) override;

		void onRecycle() override;

		virtual int32 handleInputEvent() override;

		virtual int32 handleWriteEvent() override;

		virtual int32 handleErrorEvent(uint32 ev) override;

	};
	typedef std::shared_ptr<CTcpConnection> CTcpConnectionPtr;
}