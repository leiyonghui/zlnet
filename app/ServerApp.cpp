#include "ServerApp.h"
#include "core/TimerWheel.h"

namespace app
{
	using namespace core::timerwheel;
	TimerWheel CServerApp::TimerScheduler(1);

	CServerApp::CServerApp() :
		_network(new network::CNetWork()),
		TimerHander(&TimerScheduler)
	{

	}

	CServerApp::~CServerApp()
	{
		delete _network;
	}

	void CServerApp::init()
	{

	}

	void CServerApp::run()
	{
		_network->start();
	}
}