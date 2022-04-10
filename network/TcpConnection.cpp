#include "TcpConnection.h"
#include "RingBuff.h"
#include "Network.h"

#ifdef __linux
#include <netinet/in.h>
#include <sys/epoll.h>
#endif // __linux


namespace network
{
	CTcpConnection::~CTcpConnection()
	{
		delete _inputBuff;
		delete _outBuff;
	}

	void CTcpConnection::onAwake(EHandlerType type, CEndPointUnPtr&& endPoint)
	{
		CConnection::onAwake(type, std::forward<CEndPointUnPtr>(endPoint));
	}

	void CTcpConnection::onRecycle()
	{
		CConnection::onRecycle();
		_inputBuff->clear();
		_outBuff->clear();
	}

	int32 CTcpConnection::handleInputEvent()
	{
		return handleRead();
	}

	int32 CTcpConnection::handleWriteEvent()
	{
		return handleWrite();
	}

#ifdef __linux
	int32 CTcpConnection::handleRead()
	{
		SWritev* writev = _inputBuff->writerv();
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
				_inputBuff->write(writeable);
				_inputBuff->write(extrabuf, cnt - writeable);
			}
			else
			{
				_inputBuff->write(cnt);
			}
			if (_inputCallback)
			{
				_inputCallback(SHARED_THIS(CConnection), _inputBuff);
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

	int32 CTcpConnection::handleWrite()
	{
		auto isWriting = _event & EPOLLOUT;
		if (!isWriting)
			return 0;
		//to do
	}

	void CTcpConnection::handleClose()
	{
		setState(EDisconnecting);
		if (_closeCallback)
		{
			_closeCallback(SHARED_THIS(CConnection));
		}
	}

	void CTcpConnection::handleError()
	{
		core_log_error("handleError", _endpoint->getSocket());
		//handleClose();
	}
#else // __liunx

	int32 CTcpConnection::handleRead()
	{

	}

#endif
}