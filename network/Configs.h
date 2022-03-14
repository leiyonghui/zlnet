#pragma once

#include "core/Configs.h"
#include "core/NonCopyable.h"

namespace network
{
	using namespace core;
	using namespace core::types;
	using namespace core::logs;

#ifdef __linux
	using SOCKET = int;
#define INVALID_SOCKET -1

#endif // __linux

}
