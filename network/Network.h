#pragma once
#include "Configs.h"
#include "EventDispatcher.h"
#include "Callbacks.h"
#include "Address.h"

namespace network
{
	class CNetWork
	{
	public:
		CNetWork();
		virtual ~CNetWork();

		void start();
		void createTcpListener(const CAddress& address);
		void createTcpConnector(const CAddress& address);
		void closeCon();
		void send(CConnectionPtr con);
	protected:
		void onNewConnection(CConnectionPtr connection);
		void onCloseConnection(CConnectionPtr connection);
		void onInputConnection(CConnectionPtr connection, CRingBuff* ringBuff);
		void onTimeOutConnect(CAddress address);

		void removeConnector(const CAddress& address);
		void removeConnection(SOCKET socket);
		//void pushMsg(CMsgBase* msg);
	protected:
		void init();
		void initSignal();
		inline void process();
		inline void processmsg();
		//inline void handlemsg(CMsgBase* msg);

		void onTimer10ms();
		void onTimer1000ms();

		bool _isStop;
		timerset::TimerSet* _timerSet;
		CEventDispatcher* _eventDispatcher;
		std::map<SOCKET, CConnectionPtr> _connections;
		std::map<CAddress, class CListener*> _listeners;
		std::map<CAddress, class CTcpConnector*> _tcpConnectors;
		//std::list<CMsgBase*> _msgqueue;

		int64 _lastclock;
	};
}