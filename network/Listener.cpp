#include "Listener.h"

namespace network
{


	IListener::~IListener()
	{

	}

	int32 IListener::handInputEvent()
	{
		return int32();
	}

	int32 IListener::handWriteEvent()
	{
		return int32();
	}

	int32 IListener::handErrorEvent()
	{
		return int32();
	}

}
