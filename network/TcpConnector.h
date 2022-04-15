#pragma once
#include "Endpoint.h"
#include "Network.h"
#include "Callbacks.h"
#include "Connection.h"

namespace network
{
	class CTcpConnector : 
		public CEventHandler,
		public CNoncopyable
	{
	public:
		CTcpConnector(const CAddress & address, CEventDispatcher* eventDispatcher);
		virtual ~CTcpConnector();

		int32 connect();

		void setMaxRetry(int32 maxRetry) { _maxRetry = maxRetry; };
		void setNewCallback(onNewConnectionCallback&& callback) { _newCallback = std::move(callback); }
		void setTimeOutCallback(onTimeoutCallback&& callback) { _timeoutCallback = std::move(callback); };
	protected:
		int32 handleInputEvent() override { return 0; }
		int32 handleWriteEvent() override;
		int32 handleErrorEvent(int32 ev) override;

		void setState(EConnectionState state) { _state = state; }
		void connecting();
		void onConnected();
		void reConnect();

		int32 _retryCount;
		int32 _maxRetry;
		int64 _retryId;
		EConnectionState _state;
		CAddress _address;
		onNewConnectionCallback _newCallback;
		onTimeoutCallback _timeoutCallback;
	};
}