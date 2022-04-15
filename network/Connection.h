#pragma once
#include "Configs.h"
#include "EventHandlers.h"
#include "Endpoint.h"
#include "Callbacks.h"

namespace network
{
	enum EConnectionState
	{
		EConnecting		=	1,		//��������
		EConnected		=	2,		//������
		EDisconnecting	=	3,		//���ڹر�
		EDisconnected	=	4,		//�ѹر�
	};

	class CConnection :
		public CEventHandler,
		public CPoolObject,
		public CNoncopyable,
		public std::enable_shared_from_this<CConnection>
	{
	public:
		CConnection(EHandlerType type);

		virtual ~CConnection() = default;

		virtual void onAwake(EHandlerType type, CEndPointUnPtr&& endPoint);

		virtual void onRecycle();

		virtual void destroyed() = 0;

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