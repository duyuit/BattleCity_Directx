#pragma once

#include "Scene.h"
#include <vector>
#include "Room.h"
#include <map>
#include "WaitRoomScene.h"
#include "Label.h"

#define maxRoomMember 4

class RoomScene : public Scene
{
public:
	RoomScene();
	RoomScene(bool again);
	~RoomScene();

	TCPSocketPtr socket;
	void Update(float dt);
	void Draw();
	void ReceivePakcet() override;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	
protected:
	Label label_room_select;
	Label label_failed;
	int time_active_failed = -1;
	Sprite*		pointer;

	int last_press = 0;
	bool isCreating = false;

	Label add_room;
	Sprite*		add_box;
	std::vector<Room *> roomVec;
	D3DXVECTOR3 pointerPosition;
	int pointerX;
	std::map<int, bool> keys;
	
};

