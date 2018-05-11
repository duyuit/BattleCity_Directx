#pragma once
#include "TCPSocket.h"
#include <winsock.h>

class SocketUtil
{
public:
	static TCPSocketPtr CreateTCPSocket();
};

inline TCPSocketPtr SocketUtil::CreateTCPSocket()
{
	SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s!=INVALID_SOCKET)
	{
		return TCPSocketPtr(new TCPSocket(s));
	}else
	{
		return nullptr;
	}
}
