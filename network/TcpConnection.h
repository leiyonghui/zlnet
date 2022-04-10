#pragma once
#include "Connection.h"

namespace network
{
	class CTcpConnection : 
		public CConnection,
		public std::enable_shared_from_this<CTcpConnection>
	{
	public:
		virtual ~CTcpConnection();

		void onAwake(EHandlerType type, CEndPointUnPtr&& endPoint);

		void onRecycle();

		virtual int32 handleInputEvent() override;

		virtual int32 handleWriteEvent() override;

	protected:
		int32 handleRead();

		void handleClose();

		void handleError();

	protected:

		class CRingBuff* _ringBuff;

	};
	typedef std::shared_ptr<CTcpConnection> CTcpConnectionPtr;
}