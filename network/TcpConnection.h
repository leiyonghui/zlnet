#pragma once
#include "Connection.h"

namespace network
{
	class CTcpConnection : 
		public CConnection
	{
	public:
		CTcpConnection();

		virtual ~CTcpConnection();

		void onAwake(EHandlerType type, CEndPointUnPtr&& endPoint);

		void onRecycle();

		virtual int32 handleInputEvent() override;

		virtual int32 handleWriteEvent() override;

		virtual int32 handleErrorEvent(int32 ev) override;

		virtual void destroyed() override;
	protected:
		int32 handleRead();

		int32 handleWrite();

		void handleClose();

		void handleError();

	protected:
		class CRingBuff* _inputBuff;
		class CRingBuff* _outBuff;
	};
	typedef std::shared_ptr<CTcpConnection> CTcpConnectionPtr;
}