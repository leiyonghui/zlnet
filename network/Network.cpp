
#include "Network.h"
#include "Configs.h"

namespace network
{
	CNetWork::CNetWork()
	{
#ifdef _WIN32
		WSADATA swaData;
		if (WSAStartup(MAKEWORD(2, 2), &swaData) != 0)
		{
			core_log_error("WSAStartup");
		}
#endif // _WIN32

	}

	CNetWork::~CNetWork()
	{
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32

	}
}


