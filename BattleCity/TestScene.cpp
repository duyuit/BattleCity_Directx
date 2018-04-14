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

	mMap = new GameMap("Resource files/map.tmx");

	this->socket = socket;
	//set position

	mPlayer = m_player;
	mPlayer->onSetID(m_player->ID);

	for(int i=1;i<5;i++)
	{
		if (i == mPlayer->ID) continue;
		Player* temp = new Player();
		temp->onSetID(i);;
		temp->SetPosition(300, 300);
		list_players.push_back(temp);
	}



	temp_pl = new Player();
}

void TestScene::Update(float dt)
{
	mPlayer->HandleKeyboard(keys);
	for(auto ele:anotherPlayerBullet)
	{
		ele->Update(dt);
	}

	/*if (mPlayer->LastDir != mPlayer->Dir)
	{*/
		OutputMemoryBitStream os;
		os.Write(Define::InfoPacket, Define::bitofTypePacket);
		os.Write(mPlayer);
		socket->Send(os.GetBufferPtr(), os.GetByteLength());
	//}

	mPlayer->Update(dt);

	for (auto ele : list_players)
	{
		ele->Update(dt);
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

			if(temp_pl->Tag==Entity::player)
			{
				for (auto ele : list_players)
				{
					if (ele->ID == temp_pl->ID)
					{
						ele->Dir = temp_pl->Dir;
						ele->SetPosition(temp_pl->GetPosition());
						break;
					}
				}
			}
			else if(temp_pl->Tag == Entity::bullet)
			{
				bool isBulletofMe = false;
				bool isExisted = false;
				for(auto ele:mPlayer->mBullet)
				{
					if (ele->ID == temp_pl->ID)
					{
						isBulletofMe = true;
						break;
					}
				}
				if(!isBulletofMe)
				{
					for (auto ele : anotherPlayerBullet)
					{
						if (temp_pl->ID == ele->ID)
						{
							isExisted = true;
							ele->isActive = true;
							ele->setMoveDirection(temp_pl->Dir);
							ele->SetPosition(temp_pl->GetPosition());

						}
					}
					if (!isExisted)
					{
						Bullet* bullet = new Bullet(temp_pl->Dir);
						bullet->ID = temp_pl->ID;
						bullet->SetPosition(temp_pl->GetPosition());
						bullet->isActive = true;
						anotherPlayerBullet.push_back(bullet);
					}
				}
				
			}
			
		}
	}


	



}

void TestScene::Draw()
{
	mMap->Draw();
	mPlayer->Draw();
	for (auto ele:list_players)
	{
		ele->Draw();
	}
	for (auto ele : anotherPlayerBullet)
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

