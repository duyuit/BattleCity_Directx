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
	mMap->GetListBrick().at(209)->BeCollideWith_Bullet(Direction::down);
	int x=mMap->GetListBrick().size();
	this->socket = socket;


	mPlayer = m_player;
	mPlayer->onSetID(m_player->ID);

	mListPlayer.push_back(mPlayer);

	//Add 4 player
	for(int i=1;i<5;i++)
	{
		if (i == mPlayer->ID) continue;
		Player* temp = new Player();
		temp->onSetID(i);;
		temp->SetPosition(300, 300);
		mListPlayer.push_back(temp);
	}
	
	//Add 16 bullet
	{
		mListBullets.push_back(new Bullet(11));
		mListBullets.push_back(new Bullet(12));
		mListBullets.push_back(new Bullet(13));
		mListBullets.push_back(new Bullet(14));
		mListBullets.push_back(new Bullet(21));
		mListBullets.push_back(new Bullet(22));
		mListBullets.push_back(new Bullet(23));
		mListBullets.push_back(new Bullet(24));
		mListBullets.push_back(new Bullet(31));
		mListBullets.push_back(new Bullet(32));
		mListBullets.push_back(new Bullet(33));
		mListBullets.push_back(new Bullet(34));
		mListBullets.push_back(new Bullet(41));
		mListBullets.push_back(new Bullet(42));
		mListBullets.push_back(new Bullet(43));
		mListBullets.push_back(new Bullet(44));
	}

	
	my_string = " .";
	myFont = NULL;
	HRESULT rs = D3DXCreateFont(GameGlobal::GetCurrentDevice()
		, 30, 10
		, FW_NORMAL, 1
		, false, DEFAULT_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &myFont);

	myRect.left = 50;
	myRect.top = GameGlobal::GetHeight() - 100;
	myRect.bottom = myRect.top + 200;
	myRect.right = myRect.left + 400;

}
int check_to_send = 0;
void TestScene::Update(float dt)
{
	
	check_to_send++;
	mPlayer->HandleKeyboard(keys, check_to_send);

	ReceivePacket();
	CheckCollision(dt);

	mMap->Update(dt);
	for (auto ele : mListPlayer)
	{
		ele->Update(dt);
	}
	/*for (auto ele : mListBullets)
	{
		ele->Update(dt);
	}*/


}

void TestScene::Draw()
{
	
	for (auto ele:mListPlayer)
	{
		ele->Draw();
	}
	for(auto ele:mListBullets)
	{
		ele->Draw();
	}
	mMap->Draw();
	if (myFont)
	{
		int delta = GameGlobal::RTT;
		if (delta != 16)
		{
			string s = "RTT: " + to_string(delta);
			myFont->DrawTextA(mPlayer->mCurrentSprite->GetSpriteHandle(), s.c_str(), -1, &myRect, DT_LEFT, D3DCOLOR_XRGB(240, 255, 255));
		}
	}
	

}

void TestScene::ReceivePacket()
{
	char* buff = static_cast<char*>(std::malloc(1024));
	size_t receivedByteCount = socket->Receive(buff, 1024);
	if (receivedByteCount>0)
	{
		InputMemoryBitStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket, Define::bitofTypePacket);
		if (typeofPacket == Define::WorldStatePacket)
		{
			int ObjectCount = 0;
			is.Read(ObjectCount);
			for (int i = 0; i<ObjectCount; i++)
			{
				int tag = 0;
				is.Read(tag, Define::bitofID);
				find_and_handle(tag, is);
			}

		}


	}
}

void TestScene::CheckCollision(float dt)
{
	vector<Brick*> listCollision = mMap->GetListBrick();


	for (size_t i = 0; i < listCollision.size(); i++)
	{
		for (auto pl : mListPlayer)
			if (GameCollision::isCollide(pl, listCollision[i], dt))
				pl->CollideWith_World();
		if (listCollision[i]->getDelete()) {
			mMap->eraseBrick(i);
			listCollision.erase(listCollision.begin() + i);
			i--;
		}
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

void TestScene::find_and_handle(int tag, InputMemoryBitStream &is)
{
	Entity::EntityTypes new_tag = (Entity::EntityTypes)tag;
	int id= 0;
	is.Read(id, Define::bitofID);
	switch (new_tag)
	{
	case Entity::player:
		
		for(auto ele:mListPlayer)
		{
			if(ele->ID== id)
			{
				ele->Read(is);
				GameGlobal::RTT = GetTickCount() - ele->last_move_time;
				return;

			}
			
		}
		break;
	
	case Entity::bullet:
		
		for (auto ele : mListBullets)
		{
			if (ele->ID == id)
			{
				ele->Read(is);
				if (!ele->isActive)
					int x = 1;
				return;

			}

		}
		break;
	case Entity::Brick:
		for (auto ele : mMap->GetListBrick())
		{
			if (ele->ID == id)
			{
				ele->Read(is);
				ele->BeCollideWith_Bullet(ele->dir);
				return;

			}

		}
		break;
			/*case Entity::item: break;
	case Entity::block: break;
	case Entity::none: break;
	default:;*/
	}

}

