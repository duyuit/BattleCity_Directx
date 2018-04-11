#pragma once
#include "Animation.h"
#include "Camera.h"
#include "Entity.h"
#include <map>
#include "TCPSocket.h"

enum MoveDirection
{
	Left, // qua trai 0
	Right,// qua phai 1
	Up,   // di len 2 
	Down, // di xuong 3 
	IDLE //4
};
class Player : public Entity
{
public:
	Player();
	~Player();

	void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	bool isMe = false;
	D3DXVECTOR2 lastPosition;
	MoveDirection Dir;
	MoveDirection LastDir;

	MoveDirection getMoveDirection();
	void setMoveDirection(MoveDirection);
	RECT GetBound();
	void onSetID(int ID);
		//xu ly input
	//gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
	void HandleKeyboard(std::map<int, bool> keys);

protected:

	//Animation   *mCurrentAnimation;
	Sprite * mCurrentSprite;
	Sprite * mLeftSprite;
	Sprite * mUpSprite;
	Sprite * mRightSprite;
	Sprite * mDownSprite;
	Sprite *m_top_sprite;

	
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void Stand();
};


