#pragma once
#include "Configs.h"
#include "EventHanders.h"

namespace network
{
	class CEndPoint;

	class CConnection : 
		public CEventHander,
		public CPoolObject<CConnection>,
		public CNoncopyable
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