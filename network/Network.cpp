#include "Network.h"
#include "Configs.h"
#include "Common.h"
#include "Listener.h"
#include "TcpListener.h"
#include "TcpConnection.h"
#include "TcpConnector.h"
#include "core/TimerSet.h"

#ifdef __linux
#include <signal.h>
#endif // __linux

namespace network
{
	CNetWork::CNetWork():
		_isStop(true), 
		_timerSet(new timerset::TimerSet()),
		_eventDispatcher(new CEventDispatcher(_timerSet)),
		_lastclock(0)
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
		if (listener->listen())
		{
			_listeners.insert({ address, listener });
			listener->setNewCallback([this](CConnectionPtr connection) {
				onNewConnection(connection);
			});
			core_log_debug("listening", address.toString());
		}
		else
		{

		}
	}

	void CNetWork::createTcpConnector(const CAddress& address)
	{
		CTcpConnector* connector = nullptr;
		if (core::find(_tcpConnectors, address, connector))
		{
			return;
		}
		connector = new CTcpConnector(address, _eventDispatcher);
		_tcpConnectors.insert({address, connector});
		connector->setNewCallback([this](CConnectionPtr connection) {
			onNewConnection(connection);
		});
		connector->connect();
	}

	void CNetWork::onNewConnection(CConnectionPtr con)
	{
		core_log_debug("new connection", con->getSocket());
		auto socket = con->getSocket();
		_connections.insert({socket, con});
		con->setInputCallback([this](CConnectionPtr connection, CRingBuff* ringBuff) {
			onInputConnection(connection, ringBuff);
		});
		con->setCloseCallback([this](CConnectionPtr connection) {
			onCloseConnection(connection);
		});
	}

	void CNetWork::onCloseConnection(CConnectionPtr connection)
	{
		core_log_debug("close connection", connection->getSocket());
		//auto socket = connection->getSocket();
		pushMsg(new CCloseMsg(connection));
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
		auto iter = _connections.find(socket);
		if (iter == _connections.end())
		{
			return;
		}
		auto& connection = iter->second;
		connection->destroyed();
		_connections.erase(iter);
		core_log_debug("ptr count:", connection.unique(), connection.use_count());
	}

	void CNetWork::onTimer1000ms()
	{
		static int32 count = 0;
		count++;
		if (count % 20 == 0)
		{
			CObjectPoolMonitor::showInfo();
		}
	}

	void CNetWork::pushMsg(CMsgBase* msg)
	{
		_msgqueue.push_back(msg);
	}

	void CNetWork::initSignal()
	{
#ifdef __linux
		signal(SIGPIPE, SIG_IGN);
#endif // __linux
	}

	inline void CNetWork::process()
	{
		auto now = TimeHelp::clock_ms().count();
		if (now - _lastclock >= 1000)
		{
			onTimer1000ms();
			_lastclock = now;
		}
		_timerSet->update(now);
		_eventDispatcher->process(4);
		processmsg();
	}

	inline void CNetWork::processmsg()
	{
		for (auto iter = _msgqueue.begin(); iter != _msgqueue.end(); iter = _msgqueue.erase(iter))
		{
			try
			{
				handlemsg(*iter);
				delete* iter;
			}
			catch (std::exception e)
			{
				delete *iter;
				core_log_error("processmsg", e.what());
			}
		}
	}

	inline void CNetWork::handlemsg(CMsgBase* base)
	{
		switch (base->_type)
		{
		case EMsgCloseCon:
		{
			CCloseMsg* msg = static_cast<CCloseMsg*>(base);
			removeConnection(msg->_connection->getSocket());
			break;
		}
		default:
			break;
		}
	}

}


