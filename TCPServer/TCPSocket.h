#pragma once
#include <WinSock2.h>
#include <memory>
#include "SocketAddress.h"
#include <string>


class TCPSocket {

public:
	~TCPSocket();
	int ID=1;
	SOCKET mSocket;
	int ChangetoDontWait(int flag);
	int Connect(const SocketAddress& inAddress);
	int Bind(const SocketAddress& inToAddress);
	int Listen(int inBackLog = 32);
	std::shared_ptr< TCPSocket > Accept(SocketAddress& inFromAddress);
	int Send(const void* inData, int inLen);
	int Receive(void* inBuffer, int inLen);
	int ReceiveBit(void* inBuffer, int inLen);
	void Close();
private:
	friend class SocketUtil;
	TCPSocket(SOCKET inSocket) : mSocket(inSocket) {}

};
typedef std::shared_ptr<TCPSocket> TCPSocketPtr;

TCPSocket::~TCPSocket()
{

}

int TCPSocket::ChangetoDontWait(int flag)
{
	u_long arg = flag;
	return  ioctlsocket(mSocket, FIONBIO, &arg);
}

void TCPSocket::Close()
{
	closesocket(mSocket);

}
int TCPSocket::Connect(const SocketAddress& inAddress)
{
	int err = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());
	if (err < 0) {
		return -1;
	}
	return NO_ERROR;
}
int TCPSocket::Bind(const SocketAddress & inToAddress)
{
	return bind(mSocket, &inToAddress.mSockAddr, inToAddress.GetSize());
}
int TCPSocket::Listen(int inBackLog)
{
	int err = listen(mSocket, inBackLog);
	if (err < 0)
	{

		return -1;
	}
	return NO_ERROR;
}

TCPSocketPtr TCPSocket::Accept(SocketAddress& inFromAddress)
{
	int length = inFromAddress.GetSize();
	SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);
	if (newSocket != INVALID_SOCKET)
	{
		return TCPSocketPtr(new TCPSocket(newSocket));
	}
	else
	{

		return nullptr;
	}
}

int TCPSocket::Send(const void* inData, int inLen)
{
	int bytesSentCount = send(mSocket, static_cast<const char*>(inData), inLen, 0);
	if (bytesSentCount < 0)
	{

		return -1;
	}
	return bytesSentCount;
}

int TCPSocket::Receive(void* inData, int inLen) {
	int bytesReceivedCount = recv(mSocket, static_cast<char*>(inData), inLen, 0);
	if (bytesReceivedCount < 0)
	{

		return -1;
	}
	return bytesReceivedCount;
}

inline int TCPSocket::ReceiveBit(void* inBuffer, int inLen)
{
	int bitReceivedCount = recv(mSocket, static_cast<char*>(inBuffer), inLen, 0);
	if (bitReceivedCount < 0)
	{

		return -1;
	}
	return bitReceivedCount*8;
}
