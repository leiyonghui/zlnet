#pragma once
#include "Configs.h"
#include "network/Network.h"

namespace app
{
	class CServerApp : TimerHander
	{
	public:
		static core::timerwheel::TimerWheel TimerScheduler;//������̬����Ϊ���������Լ�������timerhander

		CServerApp();

		virtual ~CServerApp();

		void init();

		void run();

	protected:
		network::CNetWork* _network;
	};
}