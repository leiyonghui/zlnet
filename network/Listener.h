#pragma once
#include "Configs.h"
#include "EventHandlers.h"
#include "Callbacks.h"

namespace network
{
	class CListener :
		public CEventHandler,
		public CNoncopyable
	{
	public:
		CListener(EHandlerType type, CEndPointUnPtr&& endpoint, CEventDispatcher* eventDispatcher);
		virtual ~CListener() = default;
		virtual bool listen() = 0;
		void setNewCallback(onNewConnectionCallback&& callback) { _newConnectionCallback = std::move(callback); };
		void setDisListenCallback(onDisListenCallback&& callback) { _disListenCallback = std::move(callback); };
	protected:
		onNewConnectionCallback _newConnectionCallback;
		onDisListenCallback _disListenCallback;
		
	};
	typedef std::shared_ptr<CListener> CListenerPtr;
}