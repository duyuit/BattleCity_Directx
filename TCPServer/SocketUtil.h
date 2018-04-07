#pragma once
#include "TCPSocket.h"
#include <vector>
using namespace std;
class SocketUtil
{
public:
	static TCPSocketPtr CreateTCPSocket();
	static fd_set* FillSetFromVector(fd_set& outSet, const std::vector<TCPSocketPtr>* inSockets);
	static void FillVectorFromSet(std::vector<TCPSocketPtr>* outSockets, const std::vector<TCPSocketPtr>* inSockets,
	                       const fd_set& inSet);
	static int Select(const std::vector<TCPSocketPtr>* inReadSet, std::vector<TCPSocketPtr>* outReadSet,
	           const vector<TCPSocketPtr>* inWriteSet, vector<TCPSocketPtr>* outWriteSet,
	           const vector<TCPSocketPtr>* inExceptSet, vector<TCPSocketPtr>* outExceptSet);
};

TCPSocketPtr SocketUtil::CreateTCPSocket()
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s!=INVALID_SOCKET)
	{
		return TCPSocketPtr(new TCPSocket(s));
	}else
	{
		return nullptr;
	}
}

fd_set* SocketUtil::FillSetFromVector(fd_set& outSet, const std::vector<TCPSocketPtr>* inSockets)
{
	if (inSockets)
	{
		FD_ZERO(&outSet);
		for (const TCPSocketPtr& socket : *inSockets)
		{
			FD_SET(socket->mSocket, &outSet);
		}
		return &outSet;
	}
	else
	{
		return nullptr;
	}
}

void SocketUtil::FillVectorFromSet(std::vector<TCPSocketPtr>* outSockets, const std::vector<TCPSocketPtr>* inSockets,
                                   const fd_set& inSet)
{
	if (inSockets && outSockets)
	{
		outSockets->clear();
		for (const TCPSocketPtr& socket : *inSockets)
		{
			if (FD_ISSET(socket->mSocket, &inSet))
			{
				outSockets->push_back(socket);
			}
		}
	}
}


int SocketUtil::Select(const std::vector<TCPSocketPtr>* inReadSet, std::vector<TCPSocketPtr>* outReadSet,
	const vector<TCPSocketPtr>* inWriteSet, vector<TCPSocketPtr>* outWriteSet,
	const vector<TCPSocketPtr>* inExceptSet, vector<TCPSocketPtr>* outExceptSet)
{     //build up some sets from our vectors     
	fd_set read, write, except;
	fd_set *readPtr = FillSetFromVector(read, inReadSet);
	fd_set *writePtr = FillSetFromVector(write, inWriteSet);
	fd_set *exceptPtr = FillSetFromVector(except, inExceptSet);
	int toRet = select(0, readPtr, writePtr, exceptPtr, nullptr);
	if (toRet > 0)
	{
		FillVectorFromSet(outReadSet, inReadSet, read); 
		FillVectorFromSet(outWriteSet, inWriteSet, write); 
		FillVectorFromSet(outExceptSet, inExceptSet, except);
	}
	return toRet;
}