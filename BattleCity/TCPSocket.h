#pragma once
#include "SocketAddress.h"
#include <wincon.h>


class TCPSocket {

	public:    
	~TCPSocket();  
	SOCKET mSocket;
	int ChangetoDontWait(int flag);
	int Connect(const SocketAddress& inAddress); 
	int Bind(const SocketAddress& inToAddress); 
	int Listen(int inBackLog = 32);
	std::shared_ptr< TCPSocket > Accept(SocketAddress& inFromAddress); 
	int Send(const void* inData, int inLen);
	int Receive(void* inBuffer, int inLen);
	void Close();
private:   
	friend class SocketUtil; 
	TCPSocket(SOCKET inSocket) : mSocket(inSocket) {}
	
};
typedef std::shared_ptr<TCPSocket> TCPSocketPtr;

inline TCPSocket::~TCPSocket()
{
	
}

inline int TCPSocket::ChangetoDontWait(int flag)
{
	u_long arg = flag;
	return  ioctlsocket(mSocket, FIONBIO, &arg);
}

inline void TCPSocket::Close()
{
	closesocket(mSocket);

}
inline int TCPSocket::Connect(const SocketAddress& inAddress)
{
	int err = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());
	if (err < 0) {
		return -1;
	}     
	return NO_ERROR;
}
inline int TCPSocket::Bind(const SocketAddress & inToAddress)
{
	return bind(mSocket,&inToAddress.mSockAddr, inToAddress.GetSize());
}
inline int TCPSocket::Listen(int inBackLog)
{
	int err = listen(mSocket, inBackLog);  
	if (err < 0)
	{

		return -1;
	}   
	return NO_ERROR;
}

inline TCPSocketPtr TCPSocket::Accept(SocketAddress& inFromAddress)
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

inline int TCPSocket::Send(const void* inData, int inLen)
{
	int bytesSentCount = send(mSocket, static_cast<const char*>(inData), inLen, 0); 
	if (bytesSentCount < 0)
	{
	
		return -1;
	}   
	return bytesSentCount;
}

inline int TCPSocket::Receive(void* inData, int inLen) {
	int bytesReceivedCount = recv(mSocket, static_cast<char*>(inData), inLen, 0);
	if (bytesReceivedCount < 0)
	{
	
		return -1;
	}
	return bytesReceivedCount;
}