#pragma once
#include "Configs.h"
#include "EventHandlers.h"

namespace network
{
	class CListener :
		public CEventHandler,
		public CNoncopyable
	{
	public:
		CListener(EHandlerType type, CEndPointUnPtr&& endpoint, CEventDispatcher* eventDispatcher);

		virtual ~CListener();

		virtual bool listen() = 0;

		void setNewCallback(onNewConnectionCallback&& callback) { _newConnectionCallback = std::move(callback); };

	protected:
		onNewConnectionCallback _newConnectionCallback;
	};
	typedef std::shared_ptr<CListener> CListenerPtr;
}