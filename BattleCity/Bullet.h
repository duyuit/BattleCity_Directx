#pragma once
#include "Entity.h"
#include "Animation.h"


class Bullet : public Entity
{
public:
	Bullet(MoveDirection dir);
	~Bullet();

	void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	bool isActive = false;
	MoveDirection getMoveDirection();
	void setMoveDirection(MoveDirection);
	 RECT GetBound() override;
protected:
	Sprite * mCurrentSprite;
	Sprite * mLeftSprite;
	Sprite * mUpSprite;
	Sprite * mRightSprite;
	Sprite * mDownSprite;
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
};

