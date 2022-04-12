#pragma once
#include "Configs.h"
#include "network/Network.h"
#include "core/TimerWheel.h"

namespace app
{
	//extern const core::timerwheel::TimerWheel WorldScheduler;

	class CServerApp : TimerHander
	{
	public:
		using TimerWheel = timerwheel::TimerWheel;
		const static TimerWheel WorldScheduler;//声明静态，因为会先析构自己在析构timerhander

		CServerApp();

		virtual ~CServerApp();

		void init();

		void run();

	protected:
		network::CNetWork* _network;
	};
}