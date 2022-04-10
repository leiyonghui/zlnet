#pragma once
#include <memory>
#include "Endpoint.h"
#include "Callbacks.h"
#include "EventDispatcher.h"

namespace network
{
	enum EHandlerType
	{
		EHandler_None = 0,
		EHandler_TcpListener = 1,
		EHandler_TcpConnection = 2,
	};

	class CEventHandler
	{
	public:
		CEventHandler() : _type(EHandler_None), _event(0), _eventDispatcher(nullptr){};

		CEventHandler(EHandlerType type, CEndPointUnPtr&& endpoint, CEventDispatcher* eventDispatcher) :
			_type(type),
			_event(0),
			_endpoint(std::move(endpoint)),
			_eventDispatcher(eventDispatcher)
		{

		}

		virtual ~CEventHandler()
		{

		}

		virtual int handleInputEvent()
		{
			return 0;
		}

		virtual int handleWriteEvent()
		{
			return 0;
		}

		virtual int handleErrorEvent(int32 ev) 
		{
			return 0;
		}

		int32 getEvent() const { return _event; }

		void updateEvent(int32 event) { _event = event; }

		SOCKET getSocket() const { _endpoint->getSocket(); }

		EHandlerType getType() const { return _type; }

		void setEventDispatcher(CEventDispatcher* eventDispatcher) { _eventDispatcher = eventDispatcher; };

	protected:
		void setType(EHandlerType type) { _type = type; }
		void setEndPoint(CEndPointUnPtr&& endpoint) { _endpoint = std::move(endpoint); }

		EHandlerType _type;
		int32 _event;
		CEndPointUnPtr _endpoint;
		CEventDispatcher* _eventDispatcher;
	};
	typedef std::shared_ptr<CEventHandler> CEventHandlerPtr;
}