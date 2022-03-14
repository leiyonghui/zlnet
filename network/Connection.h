#pragma once
#include "Configs.h"

namespace network
{
	class CEndPoint;

	class CConnection : public CNoncopyable
	{
	public:
		CConnection(CEndPoint* endPoint);

		virtual ~CConnection();

	private:
		CEndPoint* _endPoint;
	};
}