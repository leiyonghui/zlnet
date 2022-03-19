#pragma once
#include "Configs.h"
#include "EventHandlers.h"

namespace network
{
	class CEndPoint;

	class CConnection : 
		public CEventHandler,
		public CPoolObject<CConnection>,
		public CNoncopyable,
		std::enable_shared_from_this<CConnection>
	{
	public:
		CConnection(CEndPoint* endPoint);

		virtual ~CConnection();

		virtual int32 handInputEvent() override;

		virtual int32 handWriteEvent() override;

		virtual int32 handErrorEvent() override;
	
	protected:
		void onAwake() {
			
		}

		void onRecycle() {
			
		}

		CEndPoint* _endPoint;
	};
}