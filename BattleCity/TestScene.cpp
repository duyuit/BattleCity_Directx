#include "TestScene.h"
#include "SocketAddress.h"
#include "SocketUtil.h"
#include "GameLog.h"
#include "SceneManager.h"
#include "RoomScene.h"

vector<RECT> source_of_explotion(bool isBig)
{
	vector<RECT> temp;
	RECT rect;
	if(isBig)
	{

		rect.left = 97; rect.top = 66; rect.right = rect.left + 62; rect.bottom = rect.top + 61; 	temp.push_back(rect);
		rect.left = 157; rect.top = 63; rect.right = rect.left + 67; rect.bottom = rect.top + 70;	temp.push_back(rect);
	}
	else
	{
		rect.left = 5; rect.top = 67; rect.right = rect.left + 26; rect.bottom = rect.top + 27; 	temp.push_back(rect);
		rect.left = 32; rect.top = 64; rect.right = rect.left + 32; rect.bottom = rect.top + 32;	temp.push_back(rect);
		rect.left = 64; rect.top = 63; rect.right = rect.left + 33; rect.bottom = rect.top + 33;	temp.push_back(rect);
	}
	
	return temp;
};

void TestScene::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
}



TestScene::TestScene(TCPSocketPtr socket, vector<Player*> list)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);

	mMap = new GameMap("Resource files/map.tmx");
	this->socket = socket;

	mListPlayer = list;
	mPlayer = mListPlayer[socket->ID - 1];
	mPlayer->isMe = true;
	//mPlayer->onSetID(mPlayer->ID);

	//mListPlayer.push_back(mPlayer);

	//Add 4 player
	for(auto pl:mListPlayer)
	{
		pl->SetSpawn();
		pl->onSetID(pl->ID);
	}
	for (int i = 1; i<5; i++)
	{
		NPC *npc = new NPC(i);
		mListNPC.push_back(npc);
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


	{
		label_time_remaing = Label("", 30, 10, D3DXVECTOR2(GameGlobal::GetWidth() - 450, 600));

		
		label_RTT = Label("", 30, 10, D3DXVECTOR2(50, GameGlobal::GetHeight() - 100));
		label_GameOver= Label("", 50, 30, D3DXVECTOR2(GameGlobal::GetWidth() / 2 - 300, GameGlobal::GetHeight() / 2));
		label_Score1= Label("", 30, 10, D3DXVECTOR2(GameGlobal::GetWidth() - 450,0), D3DCOLOR_XRGB(255, 242, 0));
		label_Score2 = Label("", 30, 10, D3DXVECTOR2(GameGlobal::GetWidth() - 450, 100), D3DCOLOR_XRGB(195, 195, 195));
		label_Score3= Label("", 30, 10, D3DXVECTOR2(GameGlobal::GetWidth() - 450, 200) ,D3DCOLOR_XRGB(34, 177, 76));
		label_Score4 = Label("", 30, 10, D3DXVECTOR2(GameGlobal::GetWidth() - 450, 300), D3DCOLOR_XRGB(237, 28, 36));
	}



}

TestScene::~TestScene()
{
	for (auto pl : mListPoint)
		delete pl;
	for (auto pl : mListAnimate)
		delete pl;

	for (auto pl : mListBullets)
		delete pl;
	for (auto pl : mListPlayer)
		delete pl;
	delete mMap;
	for (auto pl : mListItems)
		delete pl;
	for (auto pl : mListNPC)
		delete pl;

}

void TestScene::Update(float dt)
{
	if (isOver)
	{
		if (GetTickCount() - last_time_over >= 2000)
		{
			
			GameGlobal::SendExitGame();
			SceneManager::GetInstance()->ReplaceScene(new RoomScene());
		}
		return;
	}
	time_remain -= dt;

	mPlayer->HandleKeyboard(keys);
	
	CheckCollision(dt);
	mMap->Update(dt);



	for (auto ele : mListPlayer)
	{
		ele->Update(dt);
	}
	for (auto ele : mListNPC)
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
	for (int i = 0; i<mListItems.size(); i++)
	{
		mListItems[i]->Update(dt);
		if (mListItems[i]->getDelete())
		{
			mListItems.erase(mListItems.begin() + i);
			i--;
		}
	}
	for (auto ele : mListPoint)
		ele->Update();
}

void TestScene::Draw()
{
	
	
	for (auto ele:mListPlayer)
	{
		ele->Draw();
	}
	for (auto ele : mListNPC)
	{
		ele->Draw();
	}
	
	mMap->Draw();
	for (auto ele : mListBullets)
	{
		ele->Draw();
	}

	for (auto item : mListItems)
		item->Draw();
	for (int i=0;i<mListAnimate.size();i++)
	{
		mListAnimate[i]->Draw();
		if (mListAnimate[i]->isFinish)
		{
			delete mListAnimate[i];
			mListAnimate.erase(mListAnimate.begin() + i);
			i--;
		}

	}
	for (int i = 0; i<mListPoint.size(); i++)
	{
		mListPoint[i]->Draw();
		if (mListPoint[i]->getIsDelete())
		{
			delete mListPoint[i];
			mListPoint.erase(mListPoint.begin() + i);
			i--;
		}

	}

	
	if (isOver)
	{
		DrawGameOver();
	}	
	label_time_remaing.Draw("Time remaining : " + std::to_string(time_remain) + "s");
	if(mPlayer->isDelete)
	{
		int delta = 4 - (GetTickCount() - mPlayer->last_time_die)/1000;
		string s = "Respawn in " + std::to_string(delta);
		label_GameOver.Draw(s);
	}

	label_Score1.Draw(mListPlayer[0]->mName + ": " + std::to_string(mListPlayer.at(0)->mScore));
	label_Score2.Draw(mListPlayer[1]->mName + ": " + std::to_string(mListPlayer.at(1)->mScore));
	label_Score3.Draw(mListPlayer[2]->mName + ": " + std::to_string(mListPlayer.at(2)->mScore));
	label_Score4.Draw(mListPlayer[3]->mName + ": " + std::to_string(mListPlayer.at(3)->mScore));

}

void TestScene::ShowScore()
{
}

void TestScene::ReceivePakcet()
{
	char* buff = static_cast<char*>(std::malloc(1024));
	size_t receivedByteCount = socket->Receive(buff, 1024);

	if (receivedByteCount > 0)
	{

		InputMemoryBitStream is(buff,
			static_cast<uint32_t> (receivedByteCount));
		int typeofPacket = 0;
		is.Read(typeofPacket, Define::bitofTypePacket);
		if (typeofPacket == Define::WorldStatePacket)
		{
			int ObjectCount = 0;
			is.Read(ObjectCount, Define::bitofID);

			for (int i = 0; i < ObjectCount; i++)
			{
				int tag = 0;
				is.Read(tag, Define::bitofID);
				find_and_handle(tag, is);
			}

		}
		else if(typeofPacket==Define::GameOver)
		{
			isOver = true;
			last_time_over = GetTickCount();
			OutputMemoryBitStream os;
			os.Write(Define::OutRoom, Define::bitofTypePacket);
			socket->Send(os.GetBufferPtr(), os.GetByteLength());
		}
		
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

		for (auto item : mListItems)
		{
			if (GameCollision::isCollide(pl, item, dt))
			{
				pl->CollisionWith(item);
				item->BeCollideWith_Player();
			}
		}
		
	}
	for (auto npc : mListNPC)
	{
		vector<Entity*> listCollision;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, npc);
		for (auto brick : listCollision)
		{
			if (brick->isDelete) continue;
			if (GameCollision::isCollide(npc, brick, dt))
				npc->CollideWith_World();
		}

	}



}



void TestScene::DrawGameOver()
{
	time_remain = 0;
	int max = 0;
	Player *pl=nullptr;
	for (auto ele : mListPlayer)
		if (ele->mScore >= max)
		{
			max = ele->mScore;
			pl = ele;
		}
	label_GameOver.Draw("GAME OVER\nPlayer Win: ");
	D3DCOLOR color;
	switch (pl->ID)
	{
	case 1: color = D3DCOLOR_XRGB(255, 242, 0); break;
	case 2: color = D3DCOLOR_XRGB(195, 195, 195); break;
	case 3: color = D3DCOLOR_XRGB(34, 177, 76); break;
	case 4: color = D3DCOLOR_XRGB(237, 28, 36); break;
	}
	Label label = Label(pl->mName, 50, 30, D3DXVECTOR2(GameGlobal::GetWidth() / 2+100 , GameGlobal::GetHeight() / 2 + 50), color);
	label.Draw();
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
				if(ele->Check_to_create_anim())
				{
					Explosion* explosion = new Explosion(ele->last_position, true);
					mListAnimate.push_back(explosion);
				}
				if(ele->mScore_send!=0 && ele->ID==mPlayer->ID)
				{
					Pointed* pointed = new Pointed(ele->mScore_send, ele->position_score);
 					mListPoint.push_back(pointed);
				}
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
				if(ele->isActive == false)
				{
					Explosion* explosion = new Explosion(ele->GetPosition(), false);
					mListAnimate.push_back(explosion);
				}
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

				is.Read(br->isDelete);
				break;
			}
		}
		break;
	case Entity::ProtectPlayerItem:
		{
			Item *add = new ProtectPlayer();
			add->Read(is);
			mListItems.push_back(add);
		}
		break;
	case Entity::UpgradeItem:
		{
			Item * add = new UpgradeItem();
			add->Read(is);
			mListItems.push_back(add);
		}
		break;
	case Entity::npc:
		{
			for(auto ele:mListNPC)
			{
				if (ele->ID == id)
				{
					ele->Read(is);
					if (ele->Check_to_create_anim())
					{
						Explosion* explosion = new Explosion(ele->last_position,true);
 						mListAnimate.push_back(explosion);
					}
				}
			}
		}
		break;
			/*case Entity::item: break;
	case Entity::block: break;
	case Entity::none: break;
	default:;*/
	}

}

