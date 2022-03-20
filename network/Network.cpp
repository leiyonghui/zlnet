#include "Network.h"
#include "Configs.h"
#include "Common.h"
#include "Listener.h"
#include "TcpListener.h"

#ifdef __linux
#include <signal.h>
#endif // __linux


namespace network
{
	CNetWork::CNetWork():_isStop(true), _eventDispatcher(new CEventDispatcher())
	{
#ifdef _WIN32
		WSADATA swaData;
		if (WSAStartup(MAKEWORD(2, 2), &swaData) != 0)
		{
			core_log_error("WSAStartup");
		}
#endif // _WIN32
		initSignal();
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

	void CNetWork::start()
	{
		_isStop = false;
		while (!_isStop)
		{
			//auto now = TimeHelp::miliseconds();
			_eventDispatcher->process(4);
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
		CEndPointPtr endPoint = CObjectPool<CEndPoint>::Instance()->create(socket, address);
		listener = new CTcpListener(endPoint, [this](CConnectionPtr connection) { onNewConnection(connection); });
		_listeners.insert({address, listener});
	}

	void CNetWork::onNewConnection(CConnectionPtr connection)
	{
	}

	void CNetWork::initSignal()
	{
#ifdef __linux
		signal(SIGPIPE, SIG_IGN);
#endif // __linux

	}
}


