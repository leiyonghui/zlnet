#pragma once
#include "Configs.h"
#include "EventHanders.h"

namespace network
{
	class CEndPoint;

	class IListener : 
		public CEventHander,
		public CNoncopyable
	{
	public:
		IListener() = default;

		virtual ~IListener();

		virtual int32 listen() = 0;

		virtual int32 accept() = 0;

		virtual int32 handInputEvent() override;

		virtual int32 handWriteEvent() override;

		virtual int32 handErrorEvent() override;

	protected:
		CEndPoint* _endpoint;
	};
}