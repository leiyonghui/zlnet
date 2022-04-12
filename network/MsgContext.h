#pragma once
#include "Configs.h"
#include "Connection.h"

namespace network
{
	enum EMsgType
	{
		EMsgCloseCon = 1,
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