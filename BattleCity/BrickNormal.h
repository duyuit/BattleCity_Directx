#pragma once
#include "Brick.h"
class BrickNormal : public Brick
{
public:
	BrickNormal(D3DXVECTOR3 position);
	~BrickNormal();

	const char* FileName();
	RECT rect();
	void Update();
	void BeCollideWith_Bullet(Direction dir) override;

	RECT GetBound();
private:
	RECT oldReg;
	RECT bound;
};

