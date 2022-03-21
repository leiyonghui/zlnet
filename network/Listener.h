#pragma once
#include "Configs.h"
#include "EventHandlers.h"
#include "Endpoint.h"
#include "Network.h"
#include "Callbacks.h"

namespace network
{
	class CListener :
		public CEventHandler,
		public CNoncopyable
	{
	public:
		CListener() = default;

		CListener(const CEndPointPtr endpoint, onNewConnectionCallback &&connectionCallback);

		virtual ~CListener();

		virtual bool listen() = 0;

		void setEndPoint(const CEndPointPtr& endpoint) { _endpoint = endpoint; }

		CEndPointPtr getEndPoint() const { return _endpoint; }

		void setConnectionCallback(onNewConnectionCallback&& connectionCallback) { _connectionCallback = std::move(connectionCallback); }

	protected:
		CEndPointPtr _endpoint;
		onNewConnectionCallback _connectionCallback;
	};
	typedef std::shared_ptr<CListener> CListenerPtr;
}