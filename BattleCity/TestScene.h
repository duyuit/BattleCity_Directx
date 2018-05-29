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
#include "ProtectPlayer.h"
#include "UpgradeItem.h"
#include "NPC.h"
#include "Explosion.h"
#include "Pointed.h"
#include "Label.h"

class TestScene : public Scene
{
public:
	TestScene(TCPSocketPtr socket, vector<Player*> list);
	~TestScene();
	void Update(float dt);
	void LoadContent();
	void Draw();
	void ShowScore();
	//void find_and_update_brick(int id);
	void ReceivePakcet() override;
	void CheckCollision(float dt);
	
	bool isReady = false;
	GameMap *mMap;
	vector<Pointed*> mListPoint;
	vector<Explosion*> mListAnimate;
	//vector<Entity*> mListObjects;
	vector<Bullet*> mListBullets;
	vector<Player* > mListPlayer;
	vector<Item* > mListItems;
	std::vector<NPC*>  mListNPC;
	void DrawGameOver();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void find_and_handle(int tag, InputMemoryBitStream &is);
protected:
	int last_time_over = 0;
	Camera *mCamera;
	Player *mPlayer;
	TCPSocketPtr socket;
	std::map<int, bool> keys;
	Label label_time_remaing;
	Label label_RTT;
	Label label_GameOver;
	Label label_Score1;
	Label label_Score2;
	Label label_Score3;
	Label label_Score4;
	bool isOver = false;
	float time_remain = 112;
	Label score_over;
};

