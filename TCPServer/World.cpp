#include "World.h"
//#include "Bullet.h"


World::World()
{
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
				bl->OnCollision();
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

	
}
int Packet_id = 0;
void World::SendWorld(std::vector<TCPSocketPtr> listClient)
{
	
	OutputMemoryBitStream os;
	os.Write(++Packet_id, Define::bitofID);
	os.Write(Define::WorldStatePacket, Define::bitofTypePacket);

	

	int count_bullet_send = 0;
	for (auto ele : mListBullets)
	{
		if (ele->isChange)
		{
			count_bullet_send++;
		}
	}
	
	int size = mListPlayer.size() + count_brick_send + count_bullet_send;
	
	os.Write(size,Define::bitofID);


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


