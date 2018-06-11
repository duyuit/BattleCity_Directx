#pragma once
#include "Entity.h"

class NPC:public Entity
{
public:
	NPC(int id);
	~NPC();
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void CollideWith_World();
	//Action mAction = Idle;
	int mLevel = 1;
	int mHeal = 2;
	int last_mHeal = 2;
	float last_random = 0;
	bool isDelete = false;

	void CollisionWith(Entity* en) override;
	D3DXVECTOR2 last_position = D3DXVECTOR2(0, 0);
	bool Check_to_create_anim();
	void Read(InputMemoryBitStream& is) override;
	void Update(float dt) override;
	RECT GetBound() override;
	void Write(OutputMemoryBitStream& os) override;
	void OnsetDir();
	Sprite * mCurrentSprite;
private:
	Sprite * mLeftSprite;
	Sprite * mUpSprite;
	Sprite * mRightSprite;
	Sprite * mDownSprite;

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void IDLE();
};

