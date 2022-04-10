#pragma once
#include "Endpoint.h"
#include "Network.h"

namespace network
{
	enum ECONNECT_STATE
	{
		ECONNECT_NONE = 0,
		ECONNECT_CON = 1,
		ECONNECT_DIS = 2,
	};

	class CConnector
	{
	public:
		CConnector(CEndPointUnPtr&& endPoint, CNetWork* network);

		virtual ~CConnector();

		int32 connect();

		void onConnected();

		void setState(ECONNECT_STATE state) { _state = state; }

	protected:
		ECONNECT_STATE _state;
		CEndPointUnPtr _endPoint;
		CNetWork* _netWork;
	};
}