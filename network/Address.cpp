#include <sstream>
#include "Address.h"
#include "Common.h"
#include "Configs.h"

namespace network
{
	CAddress::CAddress():_ip(0),_port(0) {

	}

	CAddress::CAddress(uint32 ip, uint16 port): _ip(hostToNetwork32(ip)), _port(hostToNetwork16(port)) {

	}

	CAddress::CAddress(std::string ip, uint16 port): _ip(0), _port(hostToNetwork16(port)) {
		String2Ip(ip.c_str(), _ip);
	}

	CAddress::CAddress(const CAddress& address): _ip(address._ip), _port(address._port){

	}

	std::string CAddress::toString() const
	{
		auto ip = networkToHost32(_ip);
		auto port = networkToHost16(_port);
		std::stringstream  ostr;
		ostr <<int32((uint8)(ip>>24))<< "." << int32((uint8)(ip>>16))<< "." << int32((uint8)(ip>>8))<< "." << int32((uint8)(ip))<<":"<< port;
		return ostr.str();
	}

	bool CAddress::String2Ip(const char* string, uint32& address)
	{
		in_addr trial;
#ifdef __linux
		if (::inet_aton(string, &trial))
		{
			address = *((int32*)((&trial)));
			return true;
		}
#endif
		return false;
	}

	bool CAddress::Ip2String(uint32 address, char* string)
	{
		address = networkToHost32(address);

		int p1, p2, p3, p4;
		p1 = address >> 24;
		p2 = (address & 0xffffff) >> 16;
		p3 = (address & 0xffff) >> 8;
		p4 = (address & 0xff);

		return sprintf(string, "%d.%d.%d.%d", p1, p2, p3, p4) > 0;
	}
}