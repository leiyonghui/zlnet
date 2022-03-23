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
		CConnector(CEndPointPtr endPoint, CNetWork* network);

		virtual ~CConnector();

		int32 connect();

		void setEndPoint(CEndPointPtr endPoint) { _endPoint = endPoint; }

		void onConnected();

		void setState(ECONNECT_STATE state) { _state = state; }

		int64 getRetryClock() const { return _retryClock; };

	protected:
		ECONNECT_STATE _state;
		CEndPointPtr _endPoint;
		CNetWork* _netWork;
		int64 _retryClock;
		int32 _retryTime;
	};
}