#include "TestScene.h"
#include "SocketAddress.h"
#include "SocketUtil.h"
#include "OutputMemoryStream.h"
#include "InputMemoryStream.h"


struct TankStruct
{
	int Direction; //1- Left,2-Right,3-Up,4-Down
	int x;
	int y;
};

void TestScene::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
}

TestScene::TestScene(int ID, D3DXVECTOR2 pos,TCPSocketPtr socket)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);
	this->socket = socket;
	//set position
	mPlayer = new Player();
	mPlayer->ID = ID;
	mPlayer->SetPosition(pos);
	for(int i=1;i<5;i++)
	{
		if (i == ID) continue;
		Player* temp = new Player();
		temp->ID = i;
		temp->SetPosition(300, 300);
		list_players.push_back(temp);
	}
}

void TestScene::Update(float dt)
{
	mPlayer->HandleKeyboard(keys);
	mPlayer->Update(dt);

	OutputMemoryStream os;
	os.Write(GameGlobal::InfoPacket);
	os.Write(mPlayer->ID);
	os.Write(static_cast<int>(mPlayer->GetPosition().x));
	os.Write(static_cast<int>(mPlayer->GetPosition().y));
	socket->Send(os.GetBufferPtr(), os.GetLength());


	char* buff = static_cast<char*>(std::malloc(1024));
	size_t receivedByteCount = socket->Receive(buff, 1024);
	if (receivedByteCount>0)
	{
		InputMemoryStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket);
		if (typeofPacket == GameGlobal::InfoPacket)
		{
			int id = 0;
			is.Read(id);
			if (id == mPlayer->ID) return;
			int x = 0, y = 0;
			is.Read(x); is.Read(y);
			for (auto ele : list_players)
			{
				if (ele->ID == id)
				{
					ele->SetPosition(x, y);
					break;
				}
				
			}
		}
	}


	



}

void TestScene::Draw()
{
	mPlayer->Draw();
	for (auto ele:list_players)
	{
		ele->Draw();
	}
}

void TestScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
}

void TestScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}

