#pragma once
#include "Camera.h"
#include "Entity.h"
#include <map>
#include "TCPSocket.h"
#include "Bullet.h"
#include <vector>
#include "GameDefine.h"


enum Action
{
	Idle,
	GoLeft,
	GoRight,
	GoUp,
	GoDown,
	Fight
};
class Player : public Entity
{
public:
	Player();
	Player(int id) { ID = id; }
	~Player();
	
	void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void CollideWith_World();
	bool isMe = false;

	Action mAction = Idle;
	Action mLastAction = Action::GoDown;
	int lastFire = 0; //Time last Fight
	int last_move_time = 0;

	void Emplace(Player* pl);
	RECT GetBound();
	void onSetID(int ID);
	void Write(OutputMemoryBitStream& os) override;
	void Read(InputMemoryBitStream& is) override;
	//xu ly input
	//gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
	void HandleKeyboard(std::map<int, bool> keys,int &check_to_send);
	Sprite * mCurrentSprite;
protected:
	

	//Animation   *mCurrentAnimation;

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


