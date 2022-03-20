#include <string.h>

#ifdef __linux
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/uio.h> 
//#include <netdb.h>
#endif // __linux

#include "Endpoint.h"


namespace network
{
	CEndPoint::CEndPoint(): _socket(INVALID_SOCKET)
	{

	}

	//CEndPoint::CEndPoint(SOCKET s, const CAddress& address): _socket(s), _address(address)
	//{
	//}

	CEndPoint::~CEndPoint()
	{
		close();
	}

	void CEndPoint::onAwake(SOCKET s, const CAddress& address)
	{
		_socket = s;
		_address = address;
	}

	void CEndPoint::onRecycle()
	{
		close();
		reset();
	}

	void CEndPoint::reset()
	{
		_address.ip(0);
		_address.port(0);
		_socket = INVALID_SOCKET;
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

#ifdef __linux
	int32 CEndPoint::setNonblock()
	{
		int32 flags = ::fcntl(_socket, F_GETFL, 0);
		flags |= O_NONBLOCK;
		if (int32 ok = ::fcntl(_socket, F_SETFL, flags)) {
			core_log_warning("SocketOpt::setNonBlock", _socket);
			return ok;
		}
		return 0;
	}

	int32 CEndPoint::bind()
	{
		sockaddr_in addr = _address.get_sockaddr_in();
		socklen_t addrlen = static_cast<socklen_t>(sizeof(addr));
		if (int32 ok = ::bind(_socket, (struct sockaddr*)&addr, addrlen))
		{
			core_log_warning("SocketOpt::bind", errno, strerror(errno));
			return ok;
		}
		return 0;
	}

	int32 CEndPoint::listen()
	{
		if (int32 ok = ::listen(_socket, SOMAXCONN))
		{
			core_log_warning("SocketOpt::listen", errno, strerror(errno));
			return ok;
		}
		return 0;
	}

	int32 CEndPoint::connect()
	{
		sockaddr_in addr = _address.get_sockaddr_in();
		socklen_t addrlen = static_cast<socklen_t>(sizeof(addr));
		if (int32 ok = ::connect(_socket, (struct sockaddr*)&addr, addrlen))
		{
			int32 error = errno;
			switch (error)
			{
			case EINPROGRESS:// The socket is nonblocking and the connection cannot be completed immediately.
				break;
			default:
			{
				core_log_warning("SocketOpt::connect", error, strerror(error));
				break;
			}
			}
			return ok;
		}
		return 0;
	}

	CEndPointPtr CEndPoint::accept()
	{
		sockaddr_in addr;
		socklen_t addrlen = static_cast<socklen_t>(sizeof(addr));
		int32 fd = ::accept(_socket, (struct sockaddr*)&addr, &addrlen);
		if (fd < 0)
		{
			core_log_warning("SocketOpt::accpet", errno, strerror(errno));
			return nullptr;
		}
		CEndPointPtr newEndPoint = CObjectPool<CEndPoint>::Instance()->create(fd, CAddress(addr));
		return newEndPoint;
	}

	int32 CEndPoint::read(char* buff, int32 len)
	{
		uint32 count = (uint32)::read(_socket, buff, (size_t)len);
		if (count < 0)
		{
			core_log_warning("SocketOpt::read", errno, strerror(errno));
		}
		return count;
	}
	
	int32 CEndPoint::readv(const iovec* iov, int32 iovcnt)
	{
		uint32 count = (uint32)::readv(_socket, iov, iovcnt);
		if (count < 0)
		{
			core_log_warning("SocketOpt::read", errno, strerror(errno));
		}
		return count;
	}

	int32 CEndPoint::write(char* buff, int32 len)
	{
		uint32 count = (uint32)::write(_socket, buff, (size_t)len);
		if (count < 0)
		{
			core_log_warning("SocketOpt::write", errno, strerror(errno));
		}
		return count;
	}

#else // __liunx
	int32 CEndPoint::setNonblock()
	{
		return 0;
	}

	int32 CEndPoint::bind()
	{
		return 0;
	}

	int32 CEndPoint::listen()
	{
		return 0;
	}

	int32 CEndPoint::connect()
	{
		return 0;
	}

	CEndPointPtr CEndPoint::accept()
	{
		return 0;
	}

	int32 CEndPoint::read(char* buff)
	{
		return 0;
	}

	int32 CEndPoint::write(char* buff, int32 len)
	{
		return 0;
	}
#endif
}