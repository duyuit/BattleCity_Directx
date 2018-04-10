// TCPServer.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include "TCPSocket.h"
#include "SocketAddress.h"
#include "SocketUtil.h"

#include <ctime>
#include "MemoryBitStream.h"
#pragma comment(lib,"WS2_32")
const int WelcomePacket = 1;
const int UpdateCountPlayer = 2;
const int LetStart = 3;
const int InfoPacket = 4;



int RandomNumber(int x,int y)
{
	return rand() % (y - x + 1) + x;
}


int main()
{
	srand(time(NULL));
	// B1 - Khoi tao
	int ID = 1;
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2, 2);
	int			ret = WSAStartup(wVersion, &wsaData);
	// B2 - Tao socket
	TCPSocketPtr socket_sever = SocketUtil::CreateTCPSocket();
	//socket_sever->ChangetoDontWait(1);

	SocketAddress receivingAddres(INADDR_ANY, 8888);

	// B3 - bind
	if (socket_sever->Bind(receivingAddres) == SOCKET_ERROR)
	{
		return 0;
	};
	// B4 - listen

	if (socket_sever->Listen(16) == SOCKET_ERROR)
	{
		return 0;
	};
	printf("Dang doi ket noi o cong 8888...");

	vector<TCPSocketPtr> readBlockSockets;
	vector<TCPSocketPtr> readableSockets;
	readBlockSockets.push_back(socket_sever);
	Entity * en = new Entity();

	while (1)
	{
		
		if (SocketUtil::Select(&readBlockSockets, &readableSockets, nullptr, nullptr, nullptr, nullptr))
		{
			for (const TCPSocketPtr& socket : readableSockets) {
				OutputMemoryBitStream os;
				if (socket == socket_sever)
				{ 
					//it's the listen socket, accept a new connection
					/*if (ID == 5)
					{
						printf("FULL Player");
						continue;
					}*/

					SocketAddress newClientAddress;
					auto newSocket = socket_sever->Accept(newClientAddress);
					newSocket->ChangetoDontWait(1);
					newSocket->ID = ID;
					readBlockSockets.push_back(newSocket);// Add socket to list 
					
					printf("\nCo ket noi moi");
					
			
					os.Write(WelcomePacket,Define::bitofTypePacket);
					os.Write(ID++, Define::bitofID);
					newSocket->Send(os.GetBufferPtr(), os.GetByteLength());

					
					if (ID == 5) //if enought player, Provide them first position by ID
					{
						
						for (auto ele : readBlockSockets)
						{
							int x = RandomNumber(150,400);
							int y = RandomNumber(300, 400);
							OutputMemoryBitStream os1;
							Entity* entity = new Entity();
							entity->ID = ele->ID;
							entity->SetPosition(x, y);

							os1.Write(LetStart, Define::bitofTypePacket);
							os1.Write(entity);

							ele->Send(os1.GetBufferPtr(), os1.GetByteLength());
						}
						break;
					}

					for (auto ele : readBlockSockets)
					{
						OutputMemoryBitStream os1;
						os1.Write(UpdateCountPlayer,Define::bitofTypePacket);
						os1.Write(ID - 1,Define::bitofID);
						ele->Send(os1.GetBufferPtr(), os1.GetByteLength());
					}

					
					
				}
				else
				{
					char* buff = static_cast<char*>( std::malloc(1024));
					size_t receivedByteCount = socket->Receive(buff, 1024);
					if (receivedByteCount > 0)
					{
						InputMemoryBitStream is(buff,
							static_cast<uint32_t> (receivedByteCount));
						int typeOfPacket = 0;
						is.Read(typeOfPacket,Define::bitofTypePacket);
						if(typeOfPacket==InfoPacket)
						{
							is.Read(en);
							for(auto ele:readBlockSockets)
							{
								if (ele->ID == en->ID) continue;
								OutputMemoryBitStream os;
								os.Write(InfoPacket,Define::bitofTypePacket);
								os.Write(en);
								ele->Send(os.GetBufferPtr(),os.GetByteLength());
							}
						}
					}

				}
			}
		}
		
	}
	
	
	return 0;
}


