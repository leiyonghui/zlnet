#pragma once
#include <memory>

namespace network
{
	class CEventHandler
	{
	public:
		CEventHandler() :_event(0) {};

		virtual int handleInputEvent() = 0;

		virtual int handleWriteEvent() = 0;

		virtual int handleErrorEvent(uint32 ev) = 0;

		uint32 getEvent() const { return _event; }

		void updateEvent(uint32 event) { _event |= event; }

	protected:
		uint32 _event;
	};
	typedef std::shared_ptr<CEventHandler> CEventHandlerPtr;
}