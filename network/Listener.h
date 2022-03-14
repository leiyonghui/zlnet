#pragma once
#include "Configs.h"

namespace network
{
	class CEndPoint;

	class Listener : public CNoncopyable
	{
	public:
		Listener() = default;

		virtual ~Listener();

		virtual int32 listen() = 0;

		virtual int32 accept() = 0;

	protected:
		CEndPoint* _endpoint;
	};
}