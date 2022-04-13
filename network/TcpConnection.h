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
	protected:
		virtual void destroyed() override;
		void close();		//主动关闭
		void closeWithDelay(int32 sec);//主动关闭
		void shutdown();

		virtual int32 handleInputEvent() override;
		virtual int32 handleWriteEvent() override;
		virtual int32 handleErrorEvent(int32 ev) override;

		int32 handleRead();
		int32 handleWrite();
		void handleClose();
		void handleError();
	protected:
		class CRingBuff* _inputBuff;
		class CRingBuff* _outBuff;

		friend class CNetwork;
	};
	typedef std::shared_ptr<CTcpConnection> CTcpConnectionPtr;
}