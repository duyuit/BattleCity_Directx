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
	void ReceivePakcet() override;
	void CheckCollision(float dt);

	bool isReady = false;
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

	ID3DXFont				*RTT_Font; //Font dung de ve chu
	RECT RTT_RECT; //RECT chua myFont
	std::string RTT_String; //Support Font

	ID3DXFont				*Ready_Font;
	RECT Ready_RECT; //RECT chua myFont
	std::string Ready_String; //Support Font
	int Ready_count = 6;
};

