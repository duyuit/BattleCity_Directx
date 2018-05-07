#include "NetWorkManager.h"

#include "SocketUtil.h"

void NetWorkManager::Handle_Packet()
{
	if (!queue_packet.empty())
	{
		Packet p = queue_packet.at(queue_packet.size() - 1);
		mWorld->HandleObject(p);
		queue_packet.pop_back();
	}
}

NetWorkManager::NetWorkManager()
{
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2, 2);
	int			ret = WSAStartup(wVersion, &wsaData);
	socket_sever = SocketUtil::CreateTCPSocket();;
	SocketAddress receivingAddres(INADDR_ANY, 8888);
	if (socket_sever->Bind(receivingAddres) == SOCKET_ERROR)
	{
		return;
	};
	if (socket_sever->Listen(16) == SOCKET_ERROR)
	{
		return;
	};
	printf("Dang doi ket noi o cong 8888...");

	readBlockSockets.push_back(socket_sever);

	mWorld = new World();
	
}


NetWorkManager::~NetWorkManager()
{
}

void NetWorkManager::Update(float dt)
{
	
	mWorld->CheckCollision(dt);
	mWorld->Update(dt);
	mWorld->SendWorld(readBlockSockets);
	
	
}

void NetWorkManager::ProcessNewClient()
{
	SocketAddress newClientAddress;
	auto newSocket = socket_sever->Accept(newClientAddress);
	newSocket->ChangetoDontWait(1);
	newSocket->ID = ID;
	readBlockSockets.push_back(newSocket);// Add socket to list 

	//Send ID to client
	OutputMemoryBitStream os;
	os.Write(Define::WelcomePacket, Define::bitofTypePacket);
	os.Write(ID++, Define::bitofID);
	newSocket->Send(os.GetBufferPtr(), os.GetByteLength());
}

void NetWorkManager::UpdatePlayerCount()
{
	for (auto ele : readBlockSockets)
	{
		OutputMemoryBitStream os1;
		os1.Write(Define::UpdateCountPlayer, Define::bitofTypePacket);
		os1.Write(ID - 1, Define::bitofID);
		ele->Send(os1.GetBufferPtr(), os1.GetByteLength());
	}

}

void NetWorkManager::ReceivePacket()
{

		

	if (SocketUtil::Select(&readBlockSockets, &readableSockets, nullptr, nullptr, nullptr, nullptr))
	{
		for (const TCPSocketPtr& socket : readableSockets) {

			if (socket == socket_sever)
			{

				ProcessNewClient();
				printf("\nCo ket noi moi");

				if (ID ==5) //if enought player, Provide them first position by ID
				{

					for (auto ele : readBlockSockets)
					{
						if (ele->ID == 0) continue;
						int x = 200; //RandomNumber(150, 400);
						int y = 200;//RandomNumber(300, 400);
									/*	int x = RandomNumber(150, 400);
									int y = RandomNumber(300, 400);*/

						OutputMemoryBitStream os1;
						PlayerServer* pl = new PlayerServer(ele->ID);
						pl->SetPosition(x, y);
						pl->mAction = Action::GoRight;
						mWorld->mListPlayer.push_back(pl);

						os1.Write(Define::LetStart, Define::bitofTypePacket);
						pl->Write(os1);
						ele->Send(os1.GetBufferPtr(), os1.GetByteLength());
					}
					break;
				}

				UpdatePlayerCount();

			}
			else
			{

				char* buff = static_cast<char*>(std::malloc(1024));
				size_t receivedByteCount = socket->Receive(buff, 1024);
				if (receivedByteCount > 0)
				{
					InputMemoryBitStream is(buff,
						static_cast<uint32_t> (receivedByteCount));
					Packet p(is);
					queue_packet.push_back(p);

				}

			}
		}
	}

}

int NetWorkManager::RandomNumber(int x, int y)
{
	return rand() % (y - x + 1) + x;
}



