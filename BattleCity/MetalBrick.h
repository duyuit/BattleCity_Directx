#pragma once
#include "Brick.h"
class MetalBrick : public Brick
{
public:
	MetalBrick(D3DXVECTOR3 position);
	~MetalBrick();

	const char* FileName();
	RECT rect();

	void BeCollideWith_Bullet(D3DXVECTOR2 BulletVelocity);
};

