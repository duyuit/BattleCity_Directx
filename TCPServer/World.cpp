#include "World.h"
//#include "Bullet.h"


World::World()
{
	{
		mListBullets.push_back(new Bullet(11,1));
		mListBullets.push_back(new Bullet(12,1));
		mListBullets.push_back(new Bullet(13,1));
		mListBullets.push_back(new Bullet(14, 1));
		mListBullets.push_back(new Bullet(21, 2));
		mListBullets.push_back(new Bullet(22, 2));
		mListBullets.push_back(new Bullet(23, 2));
		mListBullets.push_back(new Bullet(24, 2));
		mListBullets.push_back(new Bullet(31, 3));
		mListBullets.push_back(new Bullet(32, 3));
		mListBullets.push_back(new Bullet(33, 3));
		mListBullets.push_back(new Bullet(34, 3));
		mListBullets.push_back(new Bullet(41, 4));
		mListBullets.push_back(new Bullet(42, 4));
		mListBullets.push_back(new Bullet(43, 4));
		mListBullets.push_back(new Bullet(44, 4));
	}
	mMap = new GameMap("Resource files/map.tmx");
	int temp = 0;
	for (int i = 0; i < 50; i++)
	{
		int x = 0; RandomNumber(235, 335);
		int y = 0; RandomNumber(37, 187);
		if (temp == 0)
		{
			x = RandomNumber(235, 335);
			y = RandomNumber(37, 187);
		}
		else if (temp == 1)
		{
			x = RandomNumber(439, 527);
			y = RandomNumber(179, 287);
		}
		else if (temp == 2)
		{
			x = RandomNumber(215, 573);
			y = RandomNumber(626, 737);
		}
		else if (temp == 3)
		{
			x = RandomNumber(52, 77);
			y = RandomNumber(395, 687);
		}
		else if (temp == 4)
		{
			x = RandomNumber(514, 635);
			y = RandomNumber(37, 91);
			temp = 0;
		}
		temp++;
		mListPosition_Random.push_back(D3DXVECTOR2(x, y));
	}
	
	for(int i=1;i<5;i++)
	{
		NPC *npc=new NPC();
		npc->ID = i;
		npc->SetPosition(GetRandomPosition());
		mListNPC.push_back(npc);
	}
	
}


World::~World()
{
}

void World::HandleObject(Packet p)
{
	int ID = p.id;
	int action = p.action;
	int time_of_packet = p.time;



	for (auto ele : mListPlayer)
	{
		if (ele->ID == ID)
		{
			ele->OnChangeAction((Action)action);
			ele->last_move_time = time_of_packet;
			if (ele->mAction == Fight)
			{
				ele->Up_ID_OfBullet();
				for (auto bullet : mListBullets)
				{
					if (bullet->ID == ele->ID_currentBullet)
					{

						bullet->SetPosition(ele->GetPosition());
						bullet->SetActive(true);
						bullet->setMoveDirection(ele->dir);
						printf("co thang ban kia\n");
						break;
					}
				}
			}
			break;
		}
	}
}

Item* World::check_time_and_add_item()
{
	if (GetTickCount() - last_time_add_item>10000)
	{
		Item* item;
		int type = rand() +100;
		D3DXVECTOR2 ran = GetRandomPosition();
		if (type % 2 == 0) item = new ProtectPlayer(D3DXVECTOR3(ran));
		else item = new UpgradeItem(D3DXVECTOR3(ran));
		mListItems.push_back(item);
	
		last_time_add_item = GetTickCount();
		return item;
	}
	return nullptr;
}


void World::find_or_create(int ID,int action,int time_of_packet)
{
	
	
}

void World::CheckCollision(float dt)
{



	for (auto pl : mListPlayer)
	{
		vector<Entity*> listCollision;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, pl);
		for (auto brick : listCollision)
		{
			if (brick->isDelete) continue;
			if (GameCollision::isCollide(pl, brick, dt))
				pl->CollideWith_World();
		}

		for(auto item:mListItems)
		{
			if (GameCollision::isCollide(pl, item, dt))
			{
				pl->CollisionWith(item);
				item->BeCollideWith_Player();
			}
		}

	}

	//Check bullet colli voi map object
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
				bl->CollisionWith(brick);
				bl->isChange = true;
				

				for(auto brick2:mMap->GetListBrick())
				{
					if (brick2->ID == brick->ID)
					{
						brick2->CollisionWith(bl);
    						count_brick_send++;
						break;
					}
				}
				//break;
				
				
			}
		}
		for(auto pl:mListPlayer)
		{
			if (bl->ID_of_player == pl->ID) continue;
			if (GameCollision::isCollide(bl, pl, dt))
			{
			
				pl->CollisionWith(bl);
				bl->CollisionWith(pl);

				if (pl->mHeal == 0)
				{//Check bullet cua Player nao
					mListPlayer.at(bl->ID_of_player - 1)->mScore += 500;
					mListPlayer.at(bl->ID_of_player - 1)->mScore_send = 500;
				}

				bl->isChange = true;
			}
		}
		for (auto npc : mListNPC)
		{
		
			if (GameCollision::isCollide(bl, npc, dt))
			{

				npc->CollisionWith(bl);
				bl->CollisionWith(npc);

				if (npc->mHeal == 0)
				{//Check bullet cua Player nao
					mListPlayer.at(bl->ID_of_player - 1)->mScore += 300;
					mListPlayer.at(bl->ID_of_player - 1)->mScore_send = 300;
					mListPlayer.at(bl->ID_of_player - 1)->position_add = npc->GetPosition();
				}

				bl->isChange = true;
			}
		}
	}
	
	for(auto npc:mListNPC)
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
void World::Update(float dt)
{

	for (auto ele : mListPlayer)
	{
		ele->Update(1.0f/60);
	}
	for (auto ele : mListNPC)
	{
		ele->Update(1.0f / 60);
	}
	for (auto ele : mListBullets)
	{
		ele->Update(1.0f / 60);
	}
	for(int i=0;i<mListItems.size();i++)
	{
		mListItems[i]->Update(dt);
		if (mListItems[i]->getDelete())
		{
			mListItems.erase(mListItems.begin() + i);
			i--;
		}
	}
	
	
}

void World::SendWorld(std::vector<TCPSocketPtr> listClient)
{
	
	OutputMemoryBitStream os;
	os.Write(Define::WorldStatePacket, Define::bitofTypePacket);

	Item* add=check_time_and_add_item();

	int count_bullet_send = 0;
	for (auto ele : mListBullets)
	{
		if (ele->isChange)
		{
			count_bullet_send++;
		}
	}
	
	int size = mListPlayer.size() + count_brick_send + count_bullet_send+mListNPC.size();
	if (add != nullptr) size += 1;

	os.Write(size,Define::bitofID);
	if (add != nullptr)
		add->Write(os);

	for (auto ele : mListPlayer)
	{
		ele->Write(os);
	}
	for (auto ele : mListNPC)
	{
		ele->Write(os);
	}
	
	for (auto ele : mListBullets)
	{
		if (ele->isChange)
		{
			ele->Write(os);
			if (!ele->isActive)
				int l = 0;

		}
	}
	for (auto ele :mMap->GetListBrick())
	{
		if (ele->isDelete)
		{
			ele->Write(os);
		}

	}



	


	

	for (auto client : listClient)
	{
		if (client->ID == 0) continue;
		int byte_send = client->Send(os.GetBufferPtr(), os.GetByteLength());
		if(byte_send<0)
			printf("Send error");

	}

	
	
	mMap->Update(0);
	count_brick_send = 0;
	for (auto ele : mListBullets)
	{
			ele->isChange = false;
	}
}


D3DXVECTOR2 World::GetRandomPosition()
{
	int i = RandomNumber(1, 49);
	return mListPosition_Random[i];
}

int World::RandomNumber(int x, int y)
{
	return rand() % (y - x + 1) + x;
}

