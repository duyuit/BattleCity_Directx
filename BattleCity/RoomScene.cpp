#include "RoomScene.h"
#include "SceneManager.h"

RoomScene::RoomScene()
{

	GameGlobal();

	pointer = new Sprite("Resource files/topOfplayer.png",RECT(),0,0, D3DCOLOR_XRGB(255, 0, 255));
	add_box= new Sprite("Resource files/plusbox.jpg");
	add_box->SetPosition(GameGlobal::GetWidth() / 2 - 50, 200);
	add_room = Label("Create Room",20,10, D3DXVECTOR2(GameGlobal::GetWidth() / 2 - 120, 600));
	Room *a = new Room(D3DXVECTOR3(100, 400, 0));
	Room *b = new Room(D3DXVECTOR3(300, 400, 0));

	roomVec.push_back(a);
	roomVec.push_back(b);
	pointerX = 0;
	pointerPosition = D3DXVECTOR3(a->getPosition().x - 20, a->getPosition().y+50, 0);



	socket = SocketUtil::CreateTCPSocket();
	string ip = "127.0.0.1";

	if (__argv[1] != NULL)
	{
		ip = string(__argv[1]);
		
	}
	SocketAddress address(inet_addr(ip.c_str()), 8888); //"127.0.0.1"
														// B4 - Ket noi
	if (socket->Connect(address) == SOCKET_ERROR)
	{
		OutputDebugStringA("failed");
	}
	else     OutputDebugStringA("successfull");

	socket->ChangetoDontWait(1);
	GameGlobal::socket = socket;

	label_room_select = Label("Room select",30, 20, D3DXVECTOR2(500, 200));
	label_failed =Label("Can't join this room ",30, 20, D3DXVECTOR2(GameGlobal::GetWidth()/2-100, GameGlobal::GetHeight()/2-50));;
}

void RoomScene::Update(float dt)
{
	
	if (keys[VK_LEFT])
	{
		if(GetTickCount()-last_press>200)
		if (pointerX > 0) {
			--pointerX;
			last_press = GetTickCount();
		}
	}
	else if (keys[VK_RIGHT])
	{
		if (GetTickCount() - last_press>200)
		if (pointerX < roomVec.size() - 1) {
			++pointerX;
			last_press = GetTickCount();
		}
	}
	else if(keys[VK_SPACE])
	{
		if(isCreating) //Send create room for Server
		{
			OutputMemoryBitStream os;
			os.Write(Define::CreateRoom, Define::bitofTypePacket);
			socket->Send(os.GetBufferPtr(), os.GetByteLength());
			SceneManager::GetInstance()->ReplaceScene(new WaitRoomScene());
			return;
		}
		else
		{
			if (roomVec[pointerX]->isPlaying || roomVec[pointerX]->isFull)
			{
				time_active_failed = GetTickCount();
			}
			else
			{
				OutputMemoryBitStream os;
				os.Write(Define::ChooseRoom, Define::bitofTypePacket);
				os.Write(pointerX + 1, Define::bitofTypePacket);
				socket->Send(os.GetBufferPtr(), os.GetByteLength());
				SceneManager::GetInstance()->ReplaceScene(new WaitRoomScene());
				return;
			}

		}
		
	}
	else if (keys[VK_DOWN])
	{
		isCreating = true;
		pointerPosition = D3DXVECTOR3(add_box->GetPosition().x, add_box->GetPosition().y + 50, 0);
		return;
	}
	else if (keys[VK_UP])
	{
		isCreating = false;
		pointerX = 0;
	}
			


	OutputMemoryBitStream os;
	os.Write(Define::UpdateCountPlayer, Define::bitofTypePacket);
	socket->Send(os.GetBufferPtr(), os.GetByteLength());


	for (int i = 0; i < roomVec.size(); ++i)
		roomVec[i]->Update();
	if (!isCreating)
	pointerPosition = D3DXVECTOR3(roomVec[pointerX]->getPosition().x - 20, roomVec[pointerX]->getPosition().y +70, 0);
}

void RoomScene::Draw()
{
	label_room_select.Draw();
	if(time_active_failed!=-1)
	{
		if (GetTickCount() - time_active_failed > 1000)
			time_active_failed = -1;
		else label_failed.Draw();
	}
	for (int i = 0; i < roomVec.size(); ++i)
		roomVec[i]->Draw();
	pointer->Draw(pointerPosition);
	add_box->Draw();
	add_room.Draw();
}

void RoomScene::ReceivePakcet()
{
	char* buff = static_cast<char*>(std::malloc(1024));
	size_t receivedByteCount = socket->Receive(buff, 1024);

	if (receivedByteCount > 0)
	{

		InputMemoryBitStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket, Define::bitofTypePacket);
		if (typeofPacket == Define::UpdateCountPlayer)
		{
			int size = 0;
			is.Read(size, Define::bitofTypePacket);
			while (roomVec.size()<size)
			{
				Room* room=new Room(roomVec[roomVec.size() - 1]->position + D3DXVECTOR3(200, 0, 0));
				roomVec.push_back(room);
			}
			while (roomVec.size()>size)
			{
				roomVec.pop_back();
			}
			for(auto room: roomVec)
			{
				room->Read(is);
			}
			
		
		}


	}
	free(buff);
}

void RoomScene::OnKeyDown(int keyCode)
{
	
	keys[keyCode] = true;

}

void RoomScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;

}

void RoomScene::ActiveFailedString()
{

}

RoomScene::~RoomScene()
{
	//Title->Release();
	//delete pointer;
	//for (auto ele : roomVec)
	//	delete ele;
}

