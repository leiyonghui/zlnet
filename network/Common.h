#pragma once
#include "Configs.h"

#ifdef __linux
#include <arpa/inet.h>
#endif // __linux

namespace network
{
	inline int CheckCPUendian()
	{
		union {
			unsigned long int i;
			unsigned char s[4];
		}c;

		c.i = 0x12345678;
		return (0x12 == c.s[0]);
	}

#define  BYTESWAP16(A) (((A&0xff00)>>8) | ((A&0x00ff)<<8))
#define  BYTESWAP32(A) (((A&(0xff00'0000))>>24) | ((A&(0x00ff'0000))>>8) | ((A&0x0000'ff00)<<8) | ((A&0x0000'00ff)<<24))

#ifdef __linux
	inline SOCKET createSocket(EPROTOCOL proto)
	{
		SOCKET fd;
		if (proto == EPROTO_TCP)
			fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		else
			fd = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (fd == INVALID_SOCKET)
			core_log_error("craete socket", errno, proto);
		return fd;
	}

	inline uint32 hostToNetwork32(uint32 host32)
	{
		return htonl(host32);
	}

	inline uint16 hostToNetwork16(uint16 host16)
	{
		return htons(host16);
	}

	inline uint32 networkToHost32(uint32 net32)
	{
		return ntohl(net32);
	}

	inline uint16 networkToHost16(uint16 net16)
	{
		return ntohs(net16);
	}
#else// __Linux
	inline SOCKET createSocket(EPROTOCOL proto)
	{

	}

	inline uint32 hostToNetwork32(uint32 host32)
	{
		return CheckCPUendian() ? host32 : BYTESWAP32(host32);//本地大端则与网络相同
	}

	inline uint16 hostToNetwork16(uint16 host16)
	{
		return CheckCPUendian() ? host16 : BYTESWAP16(host16);
	}

	inline uint32 networkToHost32(uint32 net32)
	{
		return CheckCPUendian() ? net32 : BYTESWAP32(net32);
	}

	inline uint16 networkToHost16(uint16 net16)
	{
		return CheckCPUendian() ? net16 : BYTESWAP16(net16);
	}
#endif
}