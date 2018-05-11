#pragma once
#include <vector>
#include "PlayerServer.h"

#include "TCPSocket.h"
#include "GameMap.h"
#include "Packet.h"
#include <map>
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
	void HandleObject(Packet p);

	void find_or_create(int ID, int action,int time_of_packet);
	void CheckCollision(float dt);
	void Update(float dt);
	void SendWorld(vector<TCPSocketPtr> listClient);
};

