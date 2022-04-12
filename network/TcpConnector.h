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

		int32 handleWriteEvent() override;

		void setMaxRetry(int32 maxRetry) { _maxRetry = maxRetry; };

		void setNewCallback(onNewConnectionCallback&& callback) { _newCallback = std::move(callback); }
	protected:
		void setState(EConnectionState state) { _state = state; }

		void connecting();

		void onConnected();

		void onDisConnect();

		void retry();

		int32 _retryCount;
		int32 _maxRetry;
		int64 _retryId;
		EConnectionState _state;
		CAddress _address;
		CEndPointUnPtr _endPoint;
		onNewConnectionCallback _newCallback;
	};
}