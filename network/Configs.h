#pragma once

#include "core/Configs.h"
#include "core/NonCopyable.h"
#include "core/ObjectPools.h"
#include "core/Common.h"
#include "core/Timers.h"

#ifdef _WIN32
#include <winsock2.h>
#endif // _WIN32


namespace network
{
	using namespace core;
	using namespace core::types;
	using namespace core::logs;

	enum EPROTOCOL
	{
		EPROTO_TCP = 0,
		EPROTO_UDP = 1,
		EPROTO_KCP = 2,
	};

#ifdef __linux
	using SOCKET = int;
#define INVALID_SOCKET -1
#endif // __linux

}

#include "Common.h"