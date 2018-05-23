#include "NetWorkManager.h"

#include "SocketUtil.h"
#include "GameLog.h"

void NetWorkManager::CreatePlayerAndSend()
{
	/*mWorld->mListPlayer.clear();
	OutputMemoryBitStream os1;
	os1.Write(Define::LetStart, Define::bitofTypePacket);
	os1.Write(readBlockSockets.size() - 1,Define::bitofTypePacket);
	for (auto ele : readBlockSockets)
	{
		if (ele->ID == 0) continue;
		PlayerServer* pl = new PlayerServer(ele->ID);
		pl->SetPosition(mWorld->GetRandomPosition());
		pl->mAction = Action::GoRight;
		pl->mName = ele->name;
		pl->ActiveShield();
		mWorld->mListPlayer.push_back(pl);
		pl->Write(os1);
		os1.Write(pl->mName);
		

	}
	for (auto ele : readBlockSockets)
	ele->Send(os1.GetBufferPtr(), os1.GetByteLength());*/
}

void NetWorkManager::Handle_Packet()
{
	while (!queue_packet.empty())
	{
		Packet p = queue_packet.at(queue_packet.size() - 1);
		mListWorld_room[p.room_id-1]->HandleObject(p);
		queue_packet.pop_back();
	}
}

void NetWorkManager::Handle_Exit(TCPSocketPtr sock)
{
	int id = sock->ID;
	int id_room = sock->ID_Room;
	for(int i=0;i < readBlockSockets.size();i++)
	{
		if(readBlockSockets[i]==sock)
		{
			readBlockSockets.erase(readBlockSockets.begin() + i);
			break;
		}
	}
	if(id_room>0)
		mListWorld_room[id_room - 1]->Handle_Exit(id);
	printf("\nSOMEONE LOGOUT");

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

	World* world = new World(); mListWorld_room.push_back(world);
	World* world1 = new World(); mListWorld_room.push_back(world1);
	
	
	
}


NetWorkManager::~NetWorkManager()
{
}
int count_to_send = 0;
void NetWorkManager::Update(float dt)
{
	count_to_send++;
	for(auto ele:mListWorld_room)
	{
		ele->CheckCollision(dt);
		ele->Update(dt);
	
		if (count_to_send == 3)
			ele->SendWorld();
	}
	if (count_to_send == 3)
		count_to_send=0;
	
	
	
}

void NetWorkManager::ProcessNewClient()
{
	SocketAddress newClientAddress;
	auto newSocket = socket_sever->Accept(newClientAddress);
	newSocket->ChangetoDontWait(1);
	readBlockSockets.push_back(newSocket);// Add socket to list 

}

void NetWorkManager::UpdatePlayerCount()
{

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

			}
			else
			{

				char* buff = static_cast<char*>(std::malloc(1024));
				size_t receivedByteCount = socket->Receive(buff, 1024);
				if (receivedByteCount > 0)
				{
					InputMemoryBitStream is(buff,
						static_cast<uint32_t> (receivedByteCount));
					int type_of_packet = 0;
					is.Read(type_of_packet, Define::bitofTypePacket);
					if (type_of_packet == Define::ExitGame)
					{
						Handle_Exit(socket);
						continue;
					}
					if(socket->ID_Room==0)
					{
						
						if(type_of_packet== Define::UpdateCountPlayer)
						{
							OutputMemoryBitStream os;
							os.Write(Define::UpdateCountPlayer, Define::bitofTypePacket);
							os.Write(mListWorld_room[0]->listClient.size(), Define::bitofTypePacket);
							os.Write(mListWorld_room[1]->listClient.size(), Define::bitofTypePacket);
							socket->Send(os.GetBufferPtr(), os.GetByteLength());
						}
						else if(type_of_packet == Define::ChooseRoom)
						{
							int room_selected = 0;
							is.Read(room_selected, Define::bitofTypePacket);
							socket->ID_Room = room_selected;
							mListWorld_room[room_selected-1]->AddMember(socket);

						}
					}
					else
					{
						
						if (mListWorld_room[socket->ID_Room-1]->isStart)
						{
					
							
							if (type_of_packet == Define::UpdateCountPlayer)
							{
								mListWorld_room[socket->ID_Room - 1]->CreatePlayerAndSend();
								continue;
							}

							Packet p(is, socket->ID_Room, type_of_packet);
							queue_packet.push_back(p);
							
						}
						else
						{
							
							if (type_of_packet == Define::UpdateCountPlayer)
							{
								mListWorld_room[socket->ID_Room - 1]->UpdatePlayerCount();
							}
							else if (type_of_packet == Define::RequestName)
							{
								string name = "";
								is.Read(name);
								socket->name = name;
							}
						}
						
					}
				
				}
				
			}
		}
		readableSockets.clear();
	}

}



