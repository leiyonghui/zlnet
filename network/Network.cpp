#include "Network.h"
#include "Configs.h"
#include "Common.h"
#include "Listener.h"
#include "TcpListener.h"
#include "TcpConnection.h"
#include "TcpConnector.h"

#ifdef __linux
#include <signal.h>
#endif // __linux

namespace network
{
	CNetWork::CNetWork():_isStop(true), _timerSet(new timerset::TimerSet()),_eventDispatcher(new CEventDispatcher(_timerSet))
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
		delete _eventDispatcher;
		for (auto& iter : _listeners)
			delete iter.second;
	}

	void CNetWork::init()
	{
		initSignal();
	}

	void CNetWork::start()
	{
		init();
		_isStop = false;
		while (!_isStop)
		{
			process();
		}
	}

	void CNetWork::createTcpListener(const CAddress& address)
	{
		CListener* listener = nullptr;
		if (core::find(_listeners, address, listener))
		{
			return;
		}
		SOCKET socket = createSocket(EPROTO_TCP);
		listener = new CTcpListener(CObjectPool<CEndPoint>::Instance()->createUnique(socket, address), _eventDispatcher);
		_listeners.insert({address, listener});
		listener->setNewCallback([this](CConnectionPtr connection) {
			onNewConnection(connection);
		});
		listener->listen();
	}

	void CNetWork::createTcpConnector(const CAddress& address)
	{
		/*CConnector* connector = nullptr;
		if (core::find(_connectors, address, connector))
		{
			return;
		}
		_connectors.insert({address, connector});*/
	}

	void CNetWork::onNewConnection(CConnectionPtr connection)
	{
		core_log_debug("new connection", connection->getSocket());
		auto socket = connection->getSocket();
		auto iter = _connections.insert({socket, connection});
		connection->setInputCallback([this](CConnectionPtr connection, CRingBuff* ringBuff) {
			onInputConnection(connection, ringBuff);
		});
		connection->setCloseCallback([this](CConnectionPtr connection) {
			onCloseConnection(connection);
		});
	}

	void CNetWork::onCloseConnection(CConnectionPtr connection)
	{
		core_log_debug("close connection", connection->getSocket());
		auto socket = connection->getSocket();
		_connections.erase(socket);
		//to do
	}

	void CNetWork::onInputConnection(CConnectionPtr connection, CRingBuff* ringBuff)
	{

	}

	void CNetWork::removeConnector(const CAddress& address)
	{
		/*CConnector* connector = nullptr;
		connector = core::find(_connectors, address, connector);
		if (!connector)
			return;*/
	}

	void CNetWork::removeConnection(SOCKET socket)
	{

	}

	void CNetWork::initSignal()
	{
#ifdef __linux
		signal(SIGPIPE, SIG_IGN);
#endif // __linux
	}

	inline void CNetWork::process()
	{
		_timerSet->update(TimeHelp::clock_ms().count());
		_eventDispatcher->process(4);
	}

}


