#include "WaitRoomScene.h"
#include "SceneManager.h"
#include "GameLog.h"


void WaitRoomScene::LoadContent()
{
	socket = GameGlobal::socket;
	
	if (__argv[1] != NULL && __argv[2] != NULL)
	{
		m_name = string(__argv[2]);

	}
	


	OutputMemoryBitStream os;
	os.Write(Define::RequestName, Define::bitofTypePacket);
	os.Write(m_name);
	socket->Send(os.GetBufferPtr(), os.GetByteLength());
	

	//Define position for the box
	int left = GameGlobal::GetWidth() / 2 - 150;
	for (int i = 0; i<4; i++)
	{
	
		Sprite* sp = new  Sprite("Resource files/box.png", RECT{ 50,0,100,50 }, 0, 0, 0, GameGlobal::mBoxTexture);
			sp->SetPosition(left, GameGlobal::GetHeight() / 2);
			box.push_back(sp);
			left += 100;
	}

	/*m_player = new Player();
	m_player->isMe = true;*/

	my_string = " .";
	myFont = NULL;
	HRESULT rs = D3DXCreateFont(GameGlobal::GetCurrentDevice(), 30, 10, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &myFont);
	
	myRect.left = GameGlobal::GetWidth() / 2 - 150;
	myRect.top = GameGlobal::GetHeight() / 2 - 100;
	myRect.bottom = myRect.top + 200;
	myRect.right = myRect.left + 400;

	label_name = Label("",30,20,D3DXVECTOR2(GameGlobal::GetWidth() / 2 - 150, GameGlobal::GetHeight() / 2 - 150));

}

int lastAdd = 0;

int timetoStart = 0;

void WaitRoomScene::ReceivePakcet()
{
	char* buff = static_cast<char*>(std::malloc(1024));
	size_t receivedByteCount = socket->Receive(buff, 1024);


	if (GetTickCount() - timetoStart >0 && timetoStart != 0)
		SceneManager::GetInstance()->ReplaceScene(new TestScene(socket, m_list_players));

	if (receivedByteCount>0)
	{
		
		InputMemoryBitStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket, Define::bitofTypePacket);
		if (typeofPacket == Define::LetStart && timetoStart == 0)
		{
			//Sau khi nhan duoc goi tin start thi nhan thong tin Position de start game
			UpdateBox(4);
			timetoStart = GetTickCount();
			int size = 0;
			is.Read(size, Define::bitofTypePacket);
			for(int i=0;i<size;i++)
			{
				int tag = 0; is.Read(tag, Define::bitofID);
				int id = 0; is.Read(id, Define::bitofID);
				Player* new_pl = new Player();
				new_pl->ID = id;
				new_pl->Read(is);
				string name = ""; is.Read(name);
				new_pl->mName = name;
				m_list_players.push_back(new_pl);

			}

		}
		else if (typeofPacket == Define::UpdateCountPlayer)
		{
			is.Read(playerCount, Define::bitofID);
			is.Read(room_name);
			UpdateBox(playerCount);

		}
		else if(typeofPacket==Define::WelcomePacket)
		{
			int id = 0;
			is.Read(id, Define::bitofID);
			socket->ID = id;
		}


	}



}

void WaitRoomScene::UpdateBox(int k)
{
	if (k<5 && k>0)
		for (int i = 0; i<k; i++)
		{
			D3DXVECTOR2 pos = box.at(i)->GetPosition();
			box.at(i)->InitWithSprite("Resource files/box.png", RECT{ 0,0,50,50 },0,0,0);
			box.at(i)->SetPosition(pos);
		}
}
void WaitRoomScene::Update(float dt)
{


	

	if(GetTickCount()-lastAdd>=500)
	{
		my_string += " .";
		if (my_string == " . . . .") my_string = " .";
		lastAdd = GetTickCount();
	}
	OutputMemoryBitStream os;
	os.Write(Define::UpdateCountPlayer, Define::bitofTypePacket);
	socket->Send(os.GetBufferPtr(), os.GetByteLength());




	
}

void WaitRoomScene::Draw()
{
	for (auto ele : box)
	{
		ele->Draw();
	}
	
	std::string m_string;
	if(timetoStart == 0)
		m_string = "WAITING FOR PLAYER" + my_string;
	else
	{ 
		m_string = "Game start in ..." + std::to_string( 5 - ((GetTickCount() - timetoStart) / 1000));
	}

	if (myFont)
	{
		myFont->DrawTextA(box.at(0)->GetSpriteHandle(),m_string.c_str(), -1, &myRect, DT_LEFT, D3DCOLOR_XRGB(240, 255, 255));
	}

	label_name.Draw(room_name);

	
}

WaitRoomScene::WaitRoomScene()
{
	LoadContent();
}


WaitRoomScene::~WaitRoomScene()
{
}
