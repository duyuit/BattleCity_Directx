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

	D3DXVECTOR2 newPosition; //position of current Player to create new Game
	TCPSocketPtr socket;
	int ID = 0; //Current ID
	int playerCount = 0; //Curren player
	string m_name = "guest";
	vector<Player*> m_list_players;

	int lastAdd = 0;

	int timetoStart = 0;
	std::vector<Sprite*> box; //box chua cac o Xanh,Do the hien so nguoi choi
	ID3DXFont				*myFont; //Font dung de ve chu
	RECT myRect; //RECT chua myFont
	std::string my_string; //Support Font
	std::map<int, bool> keys;
	string room_name;
	Label label_name;
	void Update(float dt);
	void LoadContent();
	void ReceivePakcet() override;
	void Draw();
	void UpdateBox(int i);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	WaitRoomScene();
	~WaitRoomScene();
};

