#pragma once
#include "Configs.h"
#include "EventHandlers.h"
#include "Endpoint.h"

namespace network
{
	class CConnection : 
		public CEventHandler,
		public CPoolObject,
		public CNoncopyable,
		std::enable_shared_from_this<CConnection>
	{
	public:
		virtual void onAwake(CEndPointPtr endPoint);

		virtual void onRecycle();

		virtual ~CConnection();

		SOCKET getSocket() const { return _endPoint->getSocket(); }
	
	protected:
		CEndPointPtr _endPoint;
	};
	typedef std::shared_ptr<CConnection> CConnectionPtr;
}