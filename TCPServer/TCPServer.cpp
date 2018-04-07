// TCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include "TCPSocket.h"
#include "SocketAddress.h"
#include "SocketUtil.h"
#include "InputMemoryStream.h"
#include "OutputMemoryStream.h"
#include <ctime>
const int WelcomePacket = 1;
const int UpdateCountPlayer = 2;
const int LetStart = 3;
const int InfoPacket = 4;
enum MoveDirection
{
	Left, // qua trai
	Right,// qua phai
	Up,   // di len
	Down, // di xuong
};
struct ObjectInfo
{

	int x, y;
	MoveDirection dir;
};

ObjectInfo *mInfor;
int RandomNumber(int x,int y)
{
	return rand() % (y - x + 1) + x;
}
void NaivelySendRoboCat(int inSocket, const ObjectInfo* inRoboCat)
{
	send(inSocket, reinterpret_cast<const char*>(inRoboCat), sizeof(ObjectInfo), 0);
}

int NaivelyReceiveRoboCat(int inSocket, ObjectInfo* outRoboCat)
{
	return recv(inSocket, reinterpret_cast<char*>(outRoboCat), sizeof(ObjectInfo), 0);
}


int _tmain(int argc, _TCHAR* argv[])
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
	mInfor = new ObjectInfo();
	
	while (1)
	{
		
		if (SocketUtil::Select(&readBlockSockets, &readableSockets, nullptr, nullptr, nullptr, nullptr))
		{
			for (const TCPSocketPtr& socket : readableSockets) {
				OutputMemoryStream os;
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
					
					
					os.Write(WelcomePacket);
					os.Write(ID++);
					newSocket->Send(os.GetBufferPtr(), os.GetLength());

					
					if (ID == 5) //if enought player, Provide them first position by ID
					{
						
						for (auto ele : readBlockSockets)
						{
							int x = RandomNumber(150,400);
							int y = RandomNumber(300, 400);
							OutputMemoryStream os1;
							os1.Write(LetStart);
							os1.Write(ele->ID);
							os1.Write(x);
							os1.Write(y);
 							ele->Send(os1.GetBufferPtr(), os1.GetLength());
						}
						break;
					}

					for (auto ele : readBlockSockets)
					{
						OutputMemoryStream os1;
						os1.Write(UpdateCountPlayer);
						os1.Write(ID - 1);
						ele->Send(os1.GetBufferPtr(), os1.GetLength());
					}

					
					
				}
				else
				{
					char* buff = static_cast<char*>( std::malloc(1024));
					size_t receivedByteCount = socket->Receive(buff, 1024);
					if (receivedByteCount > 0)
					{
						InputMemoryStream is(buff,
							static_cast<uint32_t> (receivedByteCount));
						int typeOfPacket = 0;
						is.Read(typeOfPacket);
						if(typeOfPacket==InfoPacket)
						{
							int id = 0; is.Read(id);
							int x = 0, y = 0; is.Read(x); is.Read(y);
							for(auto ele:readBlockSockets)
							{
								OutputMemoryStream os;
								if (ele->ID == id) continue;
								os.Write(InfoPacket); os.Write(id); os.Write(x); os.Write(y);
								ele->Send(os.GetBufferPtr(), os.GetLength());
							}
						}
					}

				}
			}
		}
		
	}
	
	
	return 0;
}


