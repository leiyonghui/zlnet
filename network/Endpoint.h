#pragma once
#include "Configs.h"
#include "Address.h"

namespace network
{
	class CEndPoint : public CNoncopyable
	{
	public:
		CEndPoint();

		~CEndPoint();
	private:
		SOCKET _socket;
		CAddress _address;
	};
}