#include "Room.h"
#include "MemoryBitStream.h"
Room::Room(D3DXVECTOR3 pos)
{
	

	greenRoom = new Sprite("Resource files/box.png");

	greenRoom->SetSourceRect(RECT{ 0, 0, greenRoom->GetWidth() / 2, greenRoom->GetHeight() / 2 });
	
	redRoom = new Sprite("Resource files/box.png");
	redRoom->SetSourceRect(RECT{ redRoom->GetWidth() / 2, redRoom->GetHeight() / 2, greenRoom->GetWidth(), greenRoom->GetHeight() });
	curNumMember = 1;
	stateRoom = greenRoom;
	position = pos;
	label_player_count = Label("", 30, 10, D3DXVECTOR2(position.x - 50, GameGlobal::GetHeight() - position.y + 10), D3DCOLOR_XRGB(255, 242, 0));
	label_name = Label("", 30, 10, D3DXVECTOR2(position.x - 50, GameGlobal::GetHeight() - position.y - 50), D3DCOLOR_XRGB(255, 242, 0));
	isDelete = false;
}
void Room::Draw() {
	stateRoom->Draw(position);
	label_name.Draw(name);


	member = (curNumMember + 48);
	if(isPlaying)
	{
		member = member + " / 2\n(Playing)";
	}
	else 
		member = member + " / 2";
	
	label_player_count.Draw(member.c_str());
}

int Room::GetMember()
{
	return curNumMember;
}

void Room::SetMember(int i)
{
	curNumMember = i;
	if (curNumMember == 2) isFull = true;
	else isFull = false;
}

D3DXVECTOR3 Room::getPosition()
{
	return position;
}
void Room::setPosition(D3DXVECTOR3 pos)
{
	position = pos;
}

void Room::SetIsPlaying(bool is)
{
	isPlaying = is;
	if(is)
	stateRoom = redRoom;
}

void Room::SetName(string s)
{
	name = s;
}

void Room::SetStatus(int room1, bool play)
{
	SetIsPlaying(play);
	SetMember(room1);
}

void Room::Read(InputMemoryBitStream& is)
{
	int room1 = 0;
	bool isStart = false;
	string  name = "";
	is.Read(room1, Define::bitofTypePacket);
	is.Read(name);
	is.Read(isStart);
	SetName(name);
	SetStatus(room1, isStart);
}

void Room::Update() {
	if (isPlaying) return;
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
