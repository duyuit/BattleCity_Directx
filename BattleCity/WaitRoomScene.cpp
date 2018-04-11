#include "WaitRoomScene.h"
#include "SceneManager.h"


void WaitRoomScene::LoadContent()
{
	
	socket = SocketUtil::CreateTCPSocket();

	SocketAddress address(inet_addr("127.0.0.1"), 8888);
	// B4 - Ket noi
	if (socket->Connect(address) == SOCKET_ERROR)
	{
		OutputDebugStringA("failed");
	}
	else     OutputDebugStringA("successfull");

	
	
	char* buff = static_cast<char*>(std::malloc(1024));
	size_t receivedByteCount = socket->Receive(buff, 1024);

	if (receivedByteCount>0)
	{
		InputMemoryBitStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket,Define::bitofTypePacket);
		if (typeofPacket ==Define::WelcomePacket)
		{
			is.Read(ID,Define::bitofID);
			socket->ChangetoDontWait(1);
		}
	}

	int left = GameGlobal::GetWidth() / 2 - 150;
	for (int i = 0; i<4; i++)
	{
			Sprite* sp = new  Sprite("Resource files/red.png");
			sp->SetPosition(left, GameGlobal::GetHeight() / 2);
			box.push_back(sp);
			left += 100;
	}

	m_player = new Player();
	m_player->isMe = true;

	my_string = " .";
	myFont = NULL;
	HRESULT rs = D3DXCreateFont(GameGlobal::GetCurrentDevice(), 30, 10, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &myFont);
	
	
}
int lastAdd = 0;

int timetoStart = 0;
void WaitRoomScene::UpdateBox(int k)
{
	if (k<5 && k>0)
		for (int i = 0; i<k; i++)
		{
			D3DXVECTOR2 pos = box.at(i)->GetPosition();
			box.at(i)->InitWithSprite("Resource files/green.png");
			box.at(i)->SetPosition(pos);
		}
}
void WaitRoomScene::Update(float dt)
{
	char* buff = static_cast<char*>(std::malloc(1024));
	size_t receivedByteCount = socket->Receive(buff, 1024);

	if(GetTickCount()-timetoStart>=3000 && timetoStart!=0)
		SceneManager::GetInstance()->ReplaceScene(new TestScene(socket,m_player));

	if (receivedByteCount>0)
	{

		InputMemoryBitStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket,Define::bitofTypePacket);
		if (typeofPacket == Define::LetStart && timetoStart == 0)
		{
			//Sau khi nhan duoc goi tin start thi nhan thong tin Position de start game
			UpdateBox(4);
			timetoStart = GetTickCount();
			is.Read(m_player);

		}
		else if (typeofPacket == Define::UpdateCountPlayer)
		{
			is.Read(playerCount,Define::bitofID);
			UpdateBox(playerCount);
			
		}
	
	
	
	}

	
	
	
	if(GetTickCount()-lastAdd>=500)
	{
		my_string += " .";
		if (my_string == " . . . .") my_string = " .";
		lastAdd = GetTickCount();
	}

}

void WaitRoomScene::Draw()
{
	for (auto ele : box)
	{
		ele->Draw();
	}
	myRect.left = GameGlobal::GetWidth() /2-150;
	myRect.top = GameGlobal::GetHeight()/2-100;
	myRect.bottom = myRect.top + 200;
	myRect.right = myRect.left + 400;
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

	
}

WaitRoomScene::WaitRoomScene()
{
	LoadContent();
}


WaitRoomScene::~WaitRoomScene()
{
}
