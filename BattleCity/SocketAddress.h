#pragma once
#include <memory>
#include <winsock.h>

class SocketAddress 
{
public: 
	sockaddr mSockAddr;
	inline SocketAddress(uint32_t inAddress, uint16_t inPort)
	{
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_addr.S_un.S_addr =inAddress;
		GetAsSockAddrIn()->sin_port = htons(inPort);
	}    
	inline SocketAddress(const sockaddr& inSockAddr)
	{
		memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
	}	
	inline SocketAddress(){};
	size_t GetSize() const { return sizeof(sockaddr); }

private:     

			
	sockaddr_in* GetAsSockAddrIn()
	{
		return reinterpret_cast<sockaddr_in*>(&mSockAddr);
	}
};
typedef std::shared_ptr<SocketAddress> SocketAddressPtr;