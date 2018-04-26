#pragma once
#include "Scene.h"
#include "TCPSocket.h"
#include "Sprite.h"
#include <vector>
#include "Player.h"
#include "TestScene.h"
#include <string>
#include "SocketUtil.h"


class WaitRoomScene:public Scene
{
public:

	TCPSocketPtr socket;
	D3DXVECTOR2 newPosition; //position of current Player to create new Game

	int ID = 0; //Current ID
	int playerCount = 0; //Curren player

	Player* m_player;


	std::vector<Sprite*> box; //box chua cac o Xanh,Do the hien so nguoi choi
	ID3DXFont				*myFont; //Font dung de ve chu
	RECT myRect; //RECT chua myFont
	std::string my_string; //Support Font

	void Update(float dt);
	void LoadContent();
	void Draw();
	void UpdateBox(int i);
	WaitRoomScene();
	~WaitRoomScene();
};

