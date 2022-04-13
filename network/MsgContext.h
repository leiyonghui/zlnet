#pragma once
#include "Configs.h"
#include "Connection.h"

namespace network
{
	enum EMsgType
	{
		EMsgCloseCon		=	1,	//关闭连接
		EMsgTimeOutCon		=	2,	//连接超时
		EMsgInputMessage	=	3,	//接收
		EMsgOutMessage		=	4,	//发送
 	};

	class CMsgBase
	{
	public:
		CMsgBase(EMsgType type) :_type(type) {};
		virtual ~CMsgBase() = default;

		EMsgType _type;
	};

	class CCloseMsg : public CMsgBase
	{
	public:
		CCloseMsg(CConnectionPtr con):CMsgBase(EMsgCloseCon), _connection(con)
		{

		}

		CConnectionPtr _connection;
	};


}