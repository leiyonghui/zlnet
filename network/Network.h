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

		void init();

		void start();

		void createTcpListener(const CAddress& address);

		void createTcpConnector(const CAddress& address);

		void onNewConnection(CConnectionPtr connection);

		void onCloseConnection(CConnectionPtr connection);

		void onInputConnection(CConnectionPtr connection);

		void removeConnector(const CAddress& address);

		void removeConnection(SOCKET socket);

	private:
		void initSignal();

		inline void process();

		void handleInputEvent(SOCKET socket);

		void handleWriteEvent(SOCKET socket);

		void handleErrorEvent(SOCKET socket);

		bool _isStop;
		CEventDispatcher* _eventDispatcher;
		std::map<SOCKET, CConnectionPtr> _connections;
		std::map<CAddress, class CListener*> _listeners;
		std::map<CAddress, class CConnector*> _connectors;
	};
}