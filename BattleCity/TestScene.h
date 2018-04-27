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
#include "GameMap.h"


class TestScene : public Scene
{
public:
	TestScene(TCPSocketPtr socket, Player* m_player);
	void Update(float dt);
	void LoadContent();
	void Draw();
	void ReceivePacket();
	void CheckCollision(float dt);

	GameMap *mMap;
	vector<Entity*> mListObjects;
	vector<Bullet*> mListBullets;
	vector<Player* > mListPlayer;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void find_and_handle(int tag, InputMemoryBitStream &is);
protected:
	Camera *mCamera;
	Player *mPlayer;
	TCPSocketPtr socket;
	std::map<int, bool> keys;

	ID3DXFont				*myFont; //Font dung de ve chu
	RECT myRect; //RECT chua myFont
	std::string my_string; //Support Font
};

