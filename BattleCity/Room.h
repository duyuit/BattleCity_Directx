#pragma once
#include "Sprite.h"
#include <string>
#include "Label.h"

class InputMemoryBitStream;
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
	void SetIsPlaying(bool is);
	void SetName(string s);
	void SetStatus(int room1, bool play);
	bool isPlaying = false;
	bool isFull = false;
	void Read(InputMemoryBitStream& is);
	string name = "";
	D3DXVECTOR3 position;
private:
	Label label_player_count;
	Label label_name;
	Sprite*		greenRoom;
	Sprite*		redRoom;
	Sprite*		stateRoom;
	int			curNumMember;
	RECT		fontPosition;
	
	std::string		member;
	

	bool isDelete;
};

