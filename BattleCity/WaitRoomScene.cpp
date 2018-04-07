#include "WaitRoomScene.h"
#include "OutputMemoryStream.h"
#include "InputMemoryStream.h"
#include "Sprite.h"
#include "SocketUtil.h"
#include "SceneManager.h"
#include "TestScene.h"
#include <string>
#include <iostream>




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
	OutputMemoryStream os;

	if (receivedByteCount>0)
	{
		InputMemoryStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket);
		if (typeofPacket ==GameGlobal::WelcomePacket)
		{
			int id = 0;
			is.Read(id);
			ID = id;
			socket->Send(os.GetBufferPtr(), os.GetLength());
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
		SceneManager::GetInstance()->ReplaceScene(new TestScene(ID,newPosition,socket));

	if (receivedByteCount>0)
	{
		InputMemoryStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket);
		if (typeofPacket == GameGlobal::LetStart && timetoStart == 0)
		{
			//Sau khi nhan duoc goi tin start thi nhan thong tin Position de start game
			UpdateBox(4);
			timetoStart = GetTickCount();
			int ID_temp = 0; 			
			is.Read(ID_temp); 
			int x = 0; 	int y = 0;
			is.Read(x); is.Read(y);
			newPosition.x = x; newPosition.y = y;
			
		
		}
		else if (typeofPacket == GameGlobal::UpdateCountPlayer)
		{
			is.Read(playerCount);
			UpdateBox(playerCount);
			
		}
	
	
	
	}

	
	
	
	if(GetTickCount()-lastAdd>=500 && timetoStart!=0)
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
