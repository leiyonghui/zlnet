#pragma once
#include "Configs.h"
#include "Connection.h"

namespace network
{
	typedef std::shared_ptr<CConnection> CConnectionPtr;

	typedef std::function<void(CConnectionPtr connection)> onNewConnectionCallback;

}
