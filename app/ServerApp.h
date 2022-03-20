#pragma once
#include "Configs.h"
#include "network/Network.h"

namespace app
{
	class CServerApp : TimerHander
	{
	public:
		static core::timerwheel::TimerWheel TimerScheduler;//声明静态，因为会先析构自己在析构timerhander

		CServerApp();

		virtual ~CServerApp();

		void init();

		void run();

	protected:
		network::CNetWork* _network;
	};
}