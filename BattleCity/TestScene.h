#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>
#include "Scene.h"
#include "Animation.h"
#include "Camera.h"
#include <map>
#include "Player.h"
#include "TCPSocket.h"
#include "MemoryBitStream.h"



class TestScene : public Scene
{
public:
	TestScene(TCPSocketPtr socket, Player* m_player);
	void Update(float dt);
	void LoadContent();
	void Draw();

	
	Player* temp_pl;
	vector<Player* > list_players;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
protected:
	Camera *mCamera;
	Player *mPlayer;
	TCPSocketPtr socket;
	std::map<int, bool> keys;
};

