#pragma once
#include "Configs.h"

namespace network
{
	class CEndPoint;

	class IListener : public CNoncopyable
	{
	public:
		IListener() = default;

		virtual ~IListener();

		virtual int32 listen() = 0;

		virtual int32 accept() = 0;

	protected:
		CEndPoint* _endpoint;
	};
}