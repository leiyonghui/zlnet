#pragma once
#include <memory>

namespace network
{
	class CEventHandler
	{
	public:
		virtual int handInputEvent() = 0;

		virtual int handWriteEvent() = 0;

		virtual int handErrorEvent() = 0;
	};
	typedef std::shared_ptr<CEventHandler> CEventHandlerPtr;
}