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
		const static TimerWheel WorldScheduler;//������̬����Ϊ���������Լ�������timerhander

		CServerApp();

		virtual ~CServerApp();

		void init();

		void run();

	protected:
		network::CNetWork* _network;
	};
}