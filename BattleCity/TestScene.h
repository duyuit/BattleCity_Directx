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

class TestScene : public Scene
{
public:
	TestScene(TCPSocketPtr socket, vector<Player*> list);
	void Update(float dt);
	void LoadContent();
	void Draw();
	//void find_and_update_brick(int id);
	void ReceivePakcet() override;
	void CheckCollision(float dt);
	void SendData() override;
	bool isReady = false;
	GameMap *mMap;
	vector<Entity*> mListObjects;
	vector<Bullet*> mListBullets;
	vector<Player* > mListPlayer;
	vector<Item* > mListItems;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void find_and_handle(int tag, InputMemoryBitStream &is);
protected:
	vector<Animation*> mListAnimate;
	Camera *mCamera;
	Player *mPlayer;
	TCPSocketPtr socket;
	std::map<int, bool> keys;

	ID3DXFont				*RTT_Font = NULL; //Font dung de ve chu
	RECT RTT_RECT; //RECT chua myFont
	std::string RTT_String; //Support Font

	ID3DXFont				*GameOver_Font = NULL;
	RECT GameOver_RECT; //RECT chua myFont
	


	ID3DXFont				*Score_font =NULL;
	RECT Pl1_RECT; //RECT chua myFont
	std::string Pl1_String; //Support Font

	
	RECT Pl2_RECT; //RECT chua myFont
	std::string Pl2_String; //Support Font


	RECT Pl3_RECT; //RECT chua myFont
	std::string Pl3_String; //Support Font
	
	RECT Pl4_RECT; //RECT chua myFont
	std::string Pl4_String; //Support Font
};

