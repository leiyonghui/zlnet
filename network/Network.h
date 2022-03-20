#pragma once
#include "Configs.h"
#include "EventDispatcher.h"
#include "Callbacks.h"

namespace network
{
	class CNetWork
	{
	public:
		CNetWork();

		~CNetWork();

		void start();

		void createTcpListener(const CAddress& address);

		void onNewConnection(CConnectionPtr connection);

	private:
		void initSignal();

		bool _isStop;
		CEventDispatcher* _eventDispatcher;
		std::map<SOCKET, CConnectionPtr>	_connections;
		std::map<CAddress, class CListener*>	_listeners;
	};
}