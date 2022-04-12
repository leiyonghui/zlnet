#pragma once
#include "Configs.h"
#include "EventHandlers.h"
#include "Endpoint.h"
#include "Callbacks.h"

namespace network
{
	enum EConnectionState
	{
		EConnecting		=	1,		//正在连接
		EConnected		=	2,		//已连接
		EDisconnecting	=	3,		//半关闭中
		EDisconnected	=	4,		//关闭
	};

	class CConnection :
		public CEventHandler,
		public CPoolObject,
		public CNoncopyable,
		public std::enable_shared_from_this<CConnection>
	{
	public:
		CConnection() :_state(EDisconnected) {};

		virtual ~CConnection();

		virtual void onAwake(EHandlerType type, CEndPointUnPtr&& endPoint);

		virtual void onRecycle();

		EConnectionState getState() { return _state; }

		void setState(EConnectionState state) { _state = state; }

		void setInputCallback(onConnectionInputCallback&& callback) { _inputCallback = std::move(callback); }

		void setCloseCallback(onConnectionCloseCallback&& callback) { _closeCallback = std::move(callback); };

	protected:
		EConnectionState _state;
		onConnectionInputCallback _inputCallback;
		onConnectionCloseCallback _closeCallback;
	};
	typedef std::shared_ptr<CConnection> CConnectionPtr;
}