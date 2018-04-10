#include "TestScene.h"
#include "SocketAddress.h"
#include "SocketUtil.h"





void TestScene::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
}

TestScene::TestScene(TCPSocketPtr socket,Player* m_player)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);
	this->socket = socket;
	//set position

	mPlayer = m_player;

	for(int i=1;i<3;i++)
	{
		if (i == mPlayer->ID) continue;
		Player* temp = new Player();
		temp->ID = i;
		temp->SetPosition(300, 300);
		list_players.push_back(temp);
	}
	temp_pl = new Player();
}

void TestScene::Update(float dt)
{
	mPlayer->HandleKeyboard(keys);
	mPlayer->Update(dt);

	if (mPlayer->lastPosition != mPlayer->GetPosition())
	{
		OutputMemoryBitStream os;
		os.Write(Define::InfoPacket,Define::bitofTypePacket);
		os.Write(mPlayer);
		socket->Send(os.GetBufferPtr(),os.GetByteLength());
	}


	char* buff = static_cast<char*>(std::malloc(1024));
	size_t receivedByteCount = socket->Receive(buff, 1024);
	if (receivedByteCount>0)
	{
		InputMemoryBitStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket,Define::bitofTypePacket);
		if (typeofPacket == Define::InfoPacket)
		{
			
			
			is.Read(temp_pl);
			if (temp_pl->ID == mPlayer->ID) return;
			for (auto ele : list_players)
			{
				if (ele->ID == temp_pl->ID)
				{
					ele->SetPosition(temp_pl->GetPosition());
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

