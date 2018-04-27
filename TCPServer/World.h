#pragma once
#include <vector>
#include "PlayerServer.h"
//#include "MemoryBitStream.h"
#include "TCPSocket.h"
#include "GameMap.h"

using namespace std;
class World
{
public:
	World();
	~World();
	std::vector<Bullet*>  mListBullets;
	GameMap *mMap;

	std::vector<PlayerServer*>  mListPlayer;
	std::vector<Entity* > mListObject;
	
	int count_brick_send = 0;
	void HandleObject(InputMemoryBitStream &is);
	bool CheckDifferent(RECT a, RECT);

	void find_or_create(int ID, int action,int time_of_packet);
	void CheckCollision(float dt);
	void Update(float dt);
	void SendWorld(vector<TCPSocketPtr> listClient);
};

