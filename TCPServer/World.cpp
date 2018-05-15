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
		int x = rand() % (1000 - 10 + 1) + 10;
		int y = rand() % (1000 - 10 + 1) + 10;
		int type = rand() +100;
		if (type % 2 == 0) item = new ProtectPlayer(D3DXVECTOR3(x, y, 0));
		else item = new UpgradeItem(D3DXVECTOR3(x, y, 0));
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
				bl->OnCollision();
				bl->isChange = true;
				//Check bullet cua Player nao
				 mListPlayer.at(bl->ID_of_player-1)->mScore += 1;
				

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
				bl->OnCollision();
				bl->isChange = true;
			}
		}
	}
	
	
			
	
	
	
}
void World::Update(float dt)
{

	for (auto ele : mListPlayer)
	{
		ele->Update(1.0f/60);
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
	
	int size = mListPlayer.size() + count_brick_send + count_bullet_send;
	if (add != nullptr) size += 1;

	os.Write(size,Define::bitofID);
	if (add != nullptr)
		add->Write(os);

	for (auto ele : mListPlayer)
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


