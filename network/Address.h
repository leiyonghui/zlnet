#pragma once
#include "Configs.h"

namespace network
{
	class CAddress
	{
	public:
		static const Address NONE;
		
		CAddress();

		CAddress(uint32 ip, uint16 port);

		CAddress(std::string ip, uint16 port);

		CAddress(const CAddress& address);

		inline uint32 ip() { return _ip; }

		inline uint16 port() { return _port; }

		inline void ip(uint32 ip) { _ip = ip; }

		inline void port(uint16 port) { _port = port; };


	private:
		uint32 _ip;
		uint16 _port;
	};
}