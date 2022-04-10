#include "TcpConnection.h"
#include "RingBuff.h"
#include "Network.h"

#ifdef __linux
#include <netinet/in.h>
#endif // __linux


namespace network
{
	CTcpConnection::~CTcpConnection()
	{
		delete _ringBuff;
	}

	void CTcpConnection::onAwake(EHandlerType type, CEndPointUnPtr&& endPoint)
	{
		CConnection::onAwake(type, std::forward<CEndPointUnPtr>(endPoint));
	}

	void CTcpConnection::onRecycle()
	{
		CConnection::onRecycle();
		_ringBuff->clear();
	}

	int32 CTcpConnection::handleInputEvent()
	{
		return handleRead();
	}

	int32 CTcpConnection::handleWriteEvent()
	{
		return int32(0);
	}

#ifdef __linux
	int32 CTcpConnection::handleRead()
	{
		SWritev* writev = _ringBuff->writerv();
		int32 writeable = writev[0].len + writev[1].len;
		constexpr int32 extralen = 65536;
		char extrabuf[extralen];
		struct iovec vec[2];
		vec[0].iov_base = writev[0].buff;
		vec[0].iov_len = writev[0].len;
		vec[1].iov_base = writev[1].buff;
		vec[1].iov_len = writev[1].len;
		vec[2].iov_base = extrabuf;
		vec[2].iov_len = extralen;
		int32 iovcnt = 3;
		if (writev[0].len >= extralen)
			iovcnt = 1;
		else if (writeable >= extralen)
			iovcnt = 2;
		int32 cnt =  _endpoint->readv(vec, iovcnt);
		if (cnt > 0)
		{
			if (cnt >= writeable)
			{
				_ringBuff->write(writeable);
				_ringBuff->write(extrabuf, cnt - writeable);
			}
			else
			{
				_ringBuff->write(cnt);
			}
			if (_network)
			{
				_network->onInputConnection(SHARED_THIS(CConnection));
			}
		}
		else if(cnt == 0)
		{
			handleClose();
		}
		else
		{
			handleError();
		}
		return cnt;
	}

	void CTcpConnection::handleClose()
	{

	}

	void CTcpConnection::handleError()
	{

	}
#else // __liunx

	int32 CTcpConnection::handleRead()
	{

	}

#endif
}