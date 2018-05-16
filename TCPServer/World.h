#pragma once
#include <vector>
#include "PlayerServer.h"

#include "TCPSocket.h"
#include "GameMap.h"
#include "Packet.h"
#include <map>
#include "UpgradeItem.h"
#include "ProtectPlayer.h"
using namespace std;
class World
{
public:
	World();
	~World();
	std::vector<Bullet*>  mListBullets;
	std::vector<Item*>  mListItems;
	int last_time_add_item = 0;
	GameMap *mMap;

	std::vector<PlayerServer*>  mListPlayer;
	std::vector<Entity* > mListObject;

	vector<D3DXVECTOR2> mListPosition_Random;
	D3DXVECTOR2 GetRandomPosition();
	int RandomNumber(int x, int y);


	int count_brick_send = 0;
	void HandleObject(Packet p);
	Item* check_time_and_add_item();
	void find_or_create(int ID, int action,int time_of_packet);
	void CheckCollision(float dt);
	void Update(float dt);
	void SendWorld(vector<TCPSocketPtr> listClient);
};

