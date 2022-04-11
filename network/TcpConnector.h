#pragma once
#include "Endpoint.h"
#include "Network.h"
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

	protected:
		void setState(EConnectionState state) { _state = state; }

		void connecting();

		void onConnected();

		void retry();

		EConnectionState _state;
		CAddress _address;
		CEndPointUnPtr _endPoint;
	};
}