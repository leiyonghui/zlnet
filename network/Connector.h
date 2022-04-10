#pragma once
#include "Endpoint.h"
#include "Network.h"
#include "Connection.h"

namespace network
{
	class CConnector
	{
	public:
		CConnector(const CAddress & address, CEventDispatcher* eventDispatcher);

		virtual ~CConnector();

		int32 connect();

		void connecting();

		void onConnected();

		void setState(EConnectionState state) { _state = state; }

	protected:
		EConnectionState _state;
		CAddress _address;
		CEventDispatcher* _eventDispatcher;
		CEndPointUnPtr _endPoint;
	};
}