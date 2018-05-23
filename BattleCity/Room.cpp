#include "Room.h"

Room::Room(D3DXVECTOR3 pos)
{
	D3DXCreateFont(GameGlobal::GetCurrentDevice()
		, 30, 10
		, FW_NORMAL, 1
		, false, DEFAULT_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &curNumMemberFont);
	greenRoom = new Sprite("Resource files/box.png");

	greenRoom->SetSourceRect(RECT{ 0, 0, greenRoom->GetWidth() / 2, greenRoom->GetHeight() / 2 });
	
	redRoom = new Sprite("Resource files/box.png");
	redRoom->SetSourceRect(RECT{ redRoom->GetWidth() / 2, redRoom->GetHeight() / 2, greenRoom->GetWidth(), greenRoom->GetHeight() });
	curNumMember = 1;
	stateRoom = greenRoom;
	position = pos;
	fontPosition = RECT{ (long)position.x - 50,
						 (long)(GameGlobal::GetHeight() - position.y) + 10,
						 (long)position.x + 50,
						 (long)(GameGlobal::GetHeight() - position.y) + 50 };
	isDelete = false;
}
void Room::Draw() {
	stateRoom->Draw(position);
	member = (curNumMember + 48);
	member = member + " / 4";
	curNumMemberFont->DrawTextA(GameGlobal::GetCurrentSpriteHandler(), member.c_str(), -1, &fontPosition, DT_LEFT, D3DCOLOR_XRGB(255, 242, 0));
}

int Room::GetMember()
{
	return curNumMember;
}

void Room::SetMember(int i)
{
	curNumMember = i;
}

D3DXVECTOR3 Room::getPosition()
{
	return position;
}
void Room::setPosition(D3DXVECTOR3 pos)
{
	position = pos;
}
void Room::Update() {
	if (curNumMember >= 4) {
		stateRoom = redRoom;
		curNumMember = 4;
	}
	else 
		stateRoom = greenRoom;
	if (curNumMember < 0) {
		curNumMember = 0;
		isDelete = true;
	}
}

Room::~Room()
{
	delete greenRoom;
	delete redRoom;
	delete stateRoom;
}
