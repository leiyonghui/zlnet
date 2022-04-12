#pragma once
#include "Configs.h"
#include "EventDispatcher.h"
#include "Callbacks.h"
#include "Address.h"
#include "MsgContext.h"

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

		void onInputConnection(CConnectionPtr connection, CRingBuff* ringBuff);

		void removeConnector(const CAddress& address);

		void removeConnection(SOCKET socket);

		void onTimer1000ms();

		void pushMsg(CMsgBase* msg);

	private:
		void initSignal();

		inline void process();

		inline void processmsg();

		inline void handlemsg(CMsgBase* msg);

		bool _isStop;
		timerset::TimerSet* _timerSet;
		CEventDispatcher* _eventDispatcher;
		std::map<SOCKET, CConnectionPtr> _connections;
		std::map<CAddress, class CListener*> _listeners;
		std::map<CAddress, class CTcpConnector*> _tcpConnectors;
		std::list<CMsgBase*> _msgqueue;

		int64 _lastclock;
	};
}