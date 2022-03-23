#pragma once
#include "Configs.h"
#include "EventHandlers.h"
#include "Endpoint.h"
#include "Network.h"

namespace network
{
	class CListener :
		public CEventHandler,
		public CNoncopyable
	{
	public:
		CListener() = default;

		CListener(const CEndPointPtr endpoint, CNetWork* network);

		virtual ~CListener();

		virtual bool listen() = 0;

		void setEndPoint(const CEndPointPtr& endpoint) { _endpoint = endpoint; }

		CEndPointPtr getEndPoint() const { return _endpoint; }

	protected:
		CEndPointPtr _endpoint;
		CNetWork* _network;
	};
	typedef std::shared_ptr<CListener> CListenerPtr;
}