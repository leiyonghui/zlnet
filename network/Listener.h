#pragma once
#include "Configs.h"
#include "EventHandlers.h"
#include "Endpoint.h"

namespace network
{
	class IListener :
		public CEventHandler,
		public CNoncopyable
	{
	public:
		IListener() = default;

		IListener(const CEndPointPtr endpoint);

		virtual ~IListener();

		virtual void listen() = 0;

		void setEndPoint(const CEndPointPtr& endpoint) { _endpoint = endpoint; }

		CEndPointPtr getEndPoint() const { return _endpoint; }

	protected:
		CEndPointPtr _endpoint;
	};
}