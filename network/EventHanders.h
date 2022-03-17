#pragma once

namespace network
{
	class CEventHander
	{
	public:
		virtual int handInputEvent() = 0;

		virtual int handWriteEvent() = 0;

		virtual int handErrorEvent() = 0;
	};
}