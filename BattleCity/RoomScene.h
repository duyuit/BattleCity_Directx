#pragma once

#include "Scene.h"
#include <vector>
#include "Room.h"
#include <map>
#include "WaitRoomScene.h"

#define maxRoomMember 4

class RoomScene : public Scene
{
public:
	RoomScene();
	~RoomScene();

	TCPSocketPtr socket;
	void Update(float dt);
	void Draw();
	void ReceivePakcet() override;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
protected:
	ID3DXFont*	Title;
	Sprite*		pointer;
	std::vector<Room *> roomVec;
	D3DXVECTOR3 pointerPosition;
	int pointerX;
	std::map<int, bool> keys;
};

