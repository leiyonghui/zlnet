#include "ServerApp.h"

namespace app
{
	using namespace core::timerwheel;

	//const core::timerwheel::TimerWheel WorldScheduler(1);

	const typename CServerApp::TimerWheel CServerApp::WorldScheduler(1);

	CServerApp::CServerApp() :
		TimerHander(const_cast<TimerWheel*>(&WorldScheduler)),
		_network(new network::CNetWork())
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