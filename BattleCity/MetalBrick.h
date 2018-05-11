#pragma once
#include "Brick.h"
class MetalBrick : public Brick
{
public:
	MetalBrick(D3DXVECTOR3 position);
	~MetalBrick();


	RECT rect();

	void BeCollideWith_Bullet();
};

