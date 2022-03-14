#include "Endpoint.h"

#ifdef __linux
#include <unistd.h>
#include <fcntl.h>
//#include <sys/socket.h>
//#include <sys/uio.h> 
//#include <netdb.h>
#endif // __linux


namespace network
{
	CEndPoint::CEndPoint(): _socket(INVALID_SOCKET)
	{

	}

	CEndPoint::CEndPoint(SOCKET s, const CAddress& address): _socket(s), _address(address)
	{
	}

	CEndPoint::~CEndPoint()
	{
		close();
	}

	void CEndPoint::close()
	{
		if (_socket == INVALID_SOCKET)
		{
			core_log_warning("close invalid socket");
			return;
		}
#ifdef __linux
		::close(_socket);
#else // __liunx

#endif
	}

	int32 CEndPoint::setNonblock()
	{
#ifdef __linux
		int32 flags = ::fcntl(_socket, F_GETFL, 0);
		flags |= O_NONBLOCK;
		if (::fcntl(_socket, F_SETFL, flags) < 0)
			core_log_warning("SocketOpt::setNonBlock", _socket);
#else // __liunx

#endif
	}
}