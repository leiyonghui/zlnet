#pragma once
#include "Configs.h"

namespace network
{
	class CEndPoint;

	class CConnection : public CNoncopyable, public CPoolObject<CConnection>
	{
	public:
		CConnection(CEndPoint* endPoint);

		virtual ~CConnection();
	
	protected:
		void onAwake() {
			
		}

		void onRecycle() {
			
		}

		CEndPoint* _endPoint;
	};
}