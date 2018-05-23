#include "RoomScene.h"
#include "SceneManager.h"

RoomScene::RoomScene()
{
	GameGlobal();
	D3DXCreateFont(GameGlobal::GetCurrentDevice()
		, 40, 20
		, FW_NORMAL, 1
		, false, DEFAULT_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &Title);
	pointer = new Sprite("Resource files/topOfplayer.png",RECT(),0,0, D3DCOLOR_XRGB(255, 0, 255));
	
	Room *a = new Room(D3DXVECTOR3(100, 400, 0));
	Room *b = new Room(D3DXVECTOR3(200, 400, 0));

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


}

void RoomScene::Update(float dt)
{
	if (keys[VK_LEFT])
	{
		if (pointerX > 0) {
			--pointerX;
		}
	}
	else
		if (keys[VK_RIGHT])
		{
			if (pointerX < roomVec.size() - 1) {
				++pointerX;
			}
		}
		else
			if (keys[VK_SPACE])
			{
				OutputMemoryBitStream os;
				os.Write(Define::ChooseRoom, Define::bitofTypePacket);
				os.Write(pointerX + 1, Define::bitofTypePacket);
				socket->Send(os.GetBufferPtr(), os.GetByteLength());
				SceneManager::GetInstance()->ReplaceScene(new WaitRoomScene());
				return;
			};


	OutputMemoryBitStream os;
	os.Write(Define::UpdateCountPlayer, Define::bitofTypePacket);
	socket->Send(os.GetBufferPtr(), os.GetByteLength());

	for (int i = 0; i < roomVec.size(); ++i)
		roomVec[i]->Update();
	pointerPosition = D3DXVECTOR3(roomVec[pointerX]->getPosition().x - 20, roomVec[pointerX]->getPosition().y + 50, 0);
}

void RoomScene::Draw()
{
	RECT titlePos = RECT{ 500,200,800,300 };
	std::string title = "Select Room";
	Title->DrawTextA(GameGlobal::GetCurrentSpriteHandler(), title.c_str(), -1, &titlePos, DT_LEFT, D3DCOLOR_XRGB(255, 242, 0));
	for (int i = 0; i < roomVec.size(); ++i)
		roomVec[i]->Draw();
	pointer->Draw(pointerPosition);
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
			int room1=0, room2=0;
			is.Read(room1, Define::bitofTypePacket);
			is.Read(room2, Define::bitofTypePacket);
			roomVec[0]->SetMember(room1);
			roomVec[1]->SetMember(room2);
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

RoomScene::~RoomScene()
{
	//Title->Release();
	//delete pointer;
	//for (auto ele : roomVec)
	//	delete ele;
}

