#include "World.h"
#include "Bullet.h"


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
	int size = mMap->GetListBrick().size();
	
}


World::~World()
{
}

void World::HandleObject(InputMemoryBitStream &is)
{
	int type=0;
	is.Read(type,Define::bitofTypePacket);

	switch (type)
	{ 
	case Define::TankPacket:
		break;
	case Define::InputPacket:
		int time_of_packet = 0;
		int ID = 0, action = 0;
		is.Read(ID, Define::bitofID); 
		is.Read(action, Define::bitofID);
		is.Read(time_of_packet);
		find_or_create(ID, action,time_of_packet);
		break;
//	default: ;
	}
}

bool World::CheckDifferent(RECT a, RECT b)
{
	if (a.left != b.left || a.right != b.right || a.top != b.top || a.bottom != b.bottom)
		return true;
	return false;
}



void World::find_or_create(int ID,int action,int time_of_packet)
{

	for(auto ele:mListPlayer)
	{
		if(ele->ID==ID)
		{
			ele->OnChangeAction((Action)action);
			ele->last_move_time = time_of_packet;
			if (ele->mAction == Fight)
			{
				
				for(auto bullet:mListBullets)
				{
					if (bullet->ID == ele->ID_currentBullet)
					{
						
						bullet->SetPosition(ele->GetPosition());
						bullet->SetActive(true);
						bullet->setMoveDirection(ele->dir);
					}
				}
			}
			break;
		}
	}
	
}

void World::CheckCollision(float dt)
{
	vector<Brick*> listCollision = mMap->GetListBrick();

	count_brick_send = 0;
	for (size_t i = 0; i < listCollision.size(); i++) 
	{
		for(auto pl: mListPlayer)
			if (GameCollision::isCollide(pl, listCollision[i], dt))
				pl->CollideWith_World();
		for (auto bl : mListBullets)
			if (GameCollision::isCollide(bl, listCollision[i], dt))
			{
				bl->OnCollision(); 
				count_brick_send++;
				listCollision[i]->BeCollideWith_Bullet(D3DXVECTOR2(bl->GetVx(), bl->GetVy()));
				
			}

		if (listCollision[i]->getDelete()) {
			mMap->eraseBrick(i);
			listCollision.erase(listCollision.begin() + i);
			i--;
		}
	}
	
			
		/*if (listCollision[i]->getTag() != Entity::EntityTypes::Water) {
			for (int k = 0; k < PlayerBullet.size(); k++) {
				if (GameCollision::isCollide(PlayerBullet[k], listCollision[i], dt)) {
					PlayerBullet[k]->CollideWith_World();
					if (listCollision[i]->getTag() == Entity::EntityTypes::Brick)
						listCollision[i]->BeCollideWith_Bullet(D3DXVECTOR2(PlayerBullet[k]->GetVx(), PlayerBullet[k]->GetVy()));
				}
			}
		}*/
	
	
}

void World::Update(float dt)
{

	for (auto ele : mListPlayer)
	{
		ele->Update(dt);
	}
	for (auto ele : mListBullets)
	{
		ele->Update(dt);
	}

	mMap->Update(dt);
}

void World::SendWorld(std::vector<TCPSocketPtr> listClient)
{
	for (auto client : listClient)
	{
		if (client->ID == 0) continue;
		OutputMemoryBitStream os;
		os.Write(Define::WorldStatePacket, Define::bitofTypePacket);
		int count_bullet_send = 0;
		for (auto ele : mListBullets)
		{
			if (ele->isActive || ele->lastActive)
			{
				count_bullet_send++;
			}
		}
		
		int size = mListPlayer.size() + count_brick_send +count_bullet_send;
		os.Write(size);
		for (auto ele : mListPlayer)
		{
			ele->Write(os);
		}

		for (auto ele : mListBullets)
		{
			if (ele->isActive || ele->lastActive)
					ele->Write(os);
		}
		
		for (auto ele : mMap->GetListBrick())
		{
				if(ele->isNeedToSend)
				ele->Write(os);

		}
	
		client->Send(os.GetBufferPtr(),os.GetByteLength());

	}
	for (auto br : mMap->GetListBrick())
		br->isNeedToSend = false;
	for (auto ele : mListBullets)
	{
		if (ele->isActive || ele->lastActive)
			ele->lastActive = false;
	}
}


