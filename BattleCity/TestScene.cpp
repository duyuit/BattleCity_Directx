#include "TestScene.h"
#include "SocketAddress.h"
#include "SocketUtil.h"
#include "GameLog.h"

vector<RECT> source_of_explotion()
{
	vector<RECT> temp;
	RECT rect;

	rect.left = 5; rect.top = 67; rect.right = rect.left + 42; rect.bottom = rect.top + 38; 	temp.push_back(rect);
	rect.left = 46; rect.top = 64; rect.right = rect.left + 49; rect.bottom = rect.top + 48;	temp.push_back(rect);
	rect.left =94; rect.top = 63; rect.right = rect.left + 51; rect.bottom = rect.top + 51;	    temp.push_back(rect);
	return temp;
};

void TestScene::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
}

TestScene::TestScene(TCPSocketPtr socket,Player* m_player)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);

	mMap = new GameMap("Resource files/map.tmx");
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

	
	RTT_String = " .";
	RTT_Font = NULL;
	HRESULT rs = D3DXCreateFont(GameGlobal::GetCurrentDevice()
		, 30, 10
		, FW_NORMAL, 1
		, false, DEFAULT_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &RTT_Font);

	Ready_Font = NULL;
	HRESULT rs1 = D3DXCreateFont(GameGlobal::GetCurrentDevice()
		, 80, 50
		, FW_NORMAL, 1
		, false, DEFAULT_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &Ready_Font);


	RTT_RECT.left = 50;
	RTT_RECT.top = GameGlobal::GetHeight() - 100;
	RTT_RECT.bottom = RTT_RECT.top + 200;
	RTT_RECT.right = RTT_RECT.left + 400;

	Ready_RECT.left =GameGlobal::GetWidth()/2 - 300;
	Ready_RECT.top = GameGlobal::GetHeight()/2;
	Ready_RECT.bottom = Ready_RECT.top + 100;
	Ready_RECT.right = Ready_RECT.left +1000;

}
int check_to_send = 0;
int lastTime_Ready = 0;
void TestScene::Update(float dt)
{
	//
	//check_to_send++;
	/*if(!isReady)
	{
		if(GetTickCount()-lastTime_Ready>=1000)
		{
			lastTime_Ready = GetTickCount();
			Ready_count--;
			if (Ready_count == 0) isReady=true;
			
		}
		return;
	}*/
	mPlayer->HandleKeyboard(keys, check_to_send);
	CheckCollision(dt);
	mMap->Update(dt);



	for (auto ele : mListPlayer)
	{
		ele->Update(dt);
	}
	for (auto ele : mListBullets)
	{
		ele->Update(dt);
	}
	for (auto ele : mListAnimate)
	{
		ele->Update(dt);
	}

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
	for (int i=0;i<mListAnimate.size();i++)
	{
		mListAnimate[i]->Draw();
		if (mListAnimate[i]->GetCurrentFrame() == mListAnimate[i]->mSourceRect.size() - 1)
		{
			mListAnimate.erase(mListAnimate.begin() + i);
			i--;
		}

	}
	if (RTT_Font)
	{
		int delta = GameGlobal::RTT;
		if (delta != 16)
		{
			RTT_String = "RTT: " + to_string(delta);
			RTT_Font->DrawTextA(mPlayer->mCurrentSprite->GetSpriteHandle(), RTT_String.c_str(), -1, &RTT_RECT, DT_LEFT, D3DCOLOR_XRGB(240, 255, 255));
		}
		
	}
	/*if(Ready_Font)
	if (!isReady)
	{
		Ready_String = "Ready!!!   " + to_string(Ready_count);
		Ready_Font->DrawTextA(mPlayer->mCurrentSprite->GetSpriteHandle(), Ready_String.c_str(), -1, &Ready_RECT, DT_LEFT, D3DCOLOR_XRGB(240, 255, 255));
	}*/

}
int last_id = 0;
void TestScene::ReceivePakcet()
{
	char* buff = static_cast<char*>(std::malloc(1024));
	size_t receivedByteCount = socket->Receive(buff, 1024);
	//GAMELOG("%i\n", receivedByteCount);
	if (receivedByteCount>0)
	{
		
		InputMemoryBitStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int Packet_id = 0;
		is.Read(Packet_id, Define::bitofID);
		if (Packet_id == 1485) return;
		
	
		GAMELOG("%i\n", Packet_id);

		int typeofPacket = 0;
		is.Read(typeofPacket, Define::bitofTypePacket);
		if (typeofPacket == Define::WorldStatePacket)
		{
			int ObjectCount = 0;
			is.Read(ObjectCount,Define::bitofID);
		
			for (int i = 0; i<ObjectCount; i++)
			{
				int tag = 0;
				is.Read(tag, Define::bitofID);
				find_and_handle(tag, is);
			}

		}
		last_id++;
	}
	free(buff);
}

void TestScene::CheckCollision(float dt)
{
	
	
	for (auto pl : mListPlayer)
	{
		vector<Entity*> listCollision;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, pl);
		for(auto brick: listCollision)
		{
			if (brick->isDelete) continue;
			if (GameCollision::isCollide(pl,brick, dt))
				pl->CollideWith_World();
		}
		
	}
	for (auto bl : mListBullets)
	{
		if (!bl->isActive) continue;
		vector<Entity*> listCollision;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, bl);
		for (auto brick : listCollision)
		{
			if (brick->isDelete) continue;
			if (GameCollision::isCollide(bl, brick, dt))
			{
				
				
				bl->isActive = false;
			}

		}

	}



}

void TestScene::SendData()
{
	OutputMemoryBitStream os;
	os.Write(Define::InputPacket, Define::bitofTypePacket);
	os.Write(mPlayer->ID, Define::bitofID);
	os.Write((int)mPlayer->mAction, Define::bitofID);
	int time_of_packet = GetTickCount();
	os.Write(time_of_packet);
	GameGlobal::socket->Send(os.GetBufferPtr(), os.GetByteLength());

}

void TestScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
}

void TestScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}
int count_brick = 0;
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
				if(id==mPlayer->ID)
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
				return;

			}

		}
		break;
	case Entity::Brick:
		for (int i = 0; i < mMap->GetListBrick().size(); i++)
		{
			Brick* br = mMap->GetListBrick().at(i);
			if (br->ID == id)
			{
				Animation *explore = new Animation("Resource files/Somethings.png", source_of_explotion(), 0.05f, D3DXCOLOR(255, 0, 255, 255));
				//explore->SetScale(D3DXVECTOR2(2, 2));
				explore->SetPosition(br->GetPosition());
				mListAnimate.push_back(explore);

				is.Read(br->isDelete);

				break;
			}
		}
		break;
			/*case Entity::item: break;
	case Entity::block: break;
	case Entity::none: break;
	default:;*/
	}

}

