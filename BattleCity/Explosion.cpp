#include "Explosion.h"

Explosion::Explosion(D3DXVECTOR2 position,bool isBig)
{
	mSmallExplode[0]	= new Sprite("Resource files/Somethings.png", RECT{   0,64, 32, 96 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	mSmallExplode[1]	= new Sprite("Resource files/Somethings.png", RECT{  32,64, 64, 96 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	mSmallExplode[2]	= new Sprite("Resource files/Somethings.png", RECT{  64,64, 96, 96 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	mBigExplode[0]		= new Sprite("Resource files/Somethings.png", RECT{  96,64,160,128 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	mBigExplode[1]		= new Sprite("Resource files/Somethings.png", RECT{ 160,64,224,128 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));

	mCurrentSprite = mSmallExplode[0];
	this->position = position;

	DelayTime = 1;
	this->isBig = isBig;
	isFinish = false;
	count = 0;
	countTime = 0;
}

void Explosion::Update(float dt)
{
	if (isFinish)
		return;
	if (count < 3) {
		if (countTime >= DelayTime) {
			mCurrentSprite = mSmallExplode[count++];
			countTime = 0;
		}
		else
			++countTime;
	}
	else if (isBig && count < 5) {
		if (countTime >= DelayTime) {
			mCurrentSprite = mBigExplode[count++ - 3];
			countTime = 0;
		}
		else
			++countTime;
	}
	else
		isFinish = true;
}

void Explosion::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey) {
	if (isFinish)
		return;
	mCurrentSprite->SetPosition(this->position);
	mCurrentSprite->Draw();
}
bool Explosion::getFinish()
{
	return isFinish;
}
Explosion::~Explosion()
{
}
