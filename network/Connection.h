#pragma once
#include "Configs.h"
#include "EventHandlers.h"
#include "Endpoint.h"

namespace network
{
	enum EConnectionState
	{
		EConnected = 1,			//已连接
		EDisconnecting = 2,		//半关闭中
		EDisconnected = 3,		//关闭
	};

	class CConnection :
		public CEventHandler,
		public CPoolObject,
		public CNoncopyable
	{
	public:
		CConnection() :_state(EDisconnected) {};

		virtual ~CConnection();

		virtual void onAwake(EHandlerType type, CEndPointUnPtr&& endPoint);

		virtual void onRecycle();

		EConnectionState getState() { return _state; }

		void setState(EConnectionState state) { _state = state; }

	protected:
		EConnectionState _state;

	};
	typedef std::shared_ptr<CConnection> CConnectionPtr;
}