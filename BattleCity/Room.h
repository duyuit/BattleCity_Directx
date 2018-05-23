#pragma once
#include "Sprite.h"
#include <string>
class Room
{
public:
	Room(D3DXVECTOR3);
	~Room();

	void Update();
	void Draw();
	int GetMember();
	void SetMember(int i);
	D3DXVECTOR3 getPosition();
	void setPosition(D3DXVECTOR3 pos);

private:
	ID3DXFont*	curNumMemberFont;
	Sprite*		greenRoom;
	Sprite*		redRoom;
	Sprite*		stateRoom;
	int			curNumMember;
	RECT		fontPosition;
	D3DXVECTOR3 position;
	std::string		member;
	
	bool isDelete;
};

