#pragma once
#include "Sprite.h"
class Explosion
{
public:
	void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	bool isFinish;
	bool getFinish();
	Explosion(D3DXVECTOR2 position,bool isBig);
	~Explosion();
protected:
	Sprite * mSmallExplode[3];
	Sprite * mBigExplode[2];
	Sprite * mCurrentSprite;
	int DelayTime;
	bool isBig;

	int count;
	int countTime;
	D3DXVECTOR2 position;
};

