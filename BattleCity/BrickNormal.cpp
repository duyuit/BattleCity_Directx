#include "BrickNormal.h"



BrickNormal::BrickNormal(D3DXVECTOR3 position)
{
	Init(position);
	Tag = EntityTypes::Brick;
	oldReg = reg;
	bound = Entity::GetBound();
}

BrickNormal::~BrickNormal(){}

const char* BrickNormal::FileName() {
	return "Resource files/MapObject.png";
}
RECT BrickNormal::rect() {
	reg.left = 0;
	reg.right = this->GetWidth();
	reg.top = 0;
	reg.bottom = this->GetHeight();

	return reg;
}

void BrickNormal::Update()
{
	if (reg.left >= reg.right || reg.top >= reg.bottom) 
	{
		isDelete = true;
	}
	if (reg.left != oldReg.left || reg.right != oldReg.right || reg.top != oldReg.top || reg.bottom != oldReg.bottom)
	{
		mSprite->SetSourceRect(reg);
		oldReg = reg;
	}
}

void BrickNormal::BeCollideWith_Bullet(Direction dir)
{
	switch (dir) 
	{ 
	case left:
			reg.left += 8;
			bound.left += 8;
			posX += 8;
			mSprite->SetPosition(posX, posY); break; 
	case right:
		reg.right -= 8;
		bound.right -= 8; break;
	case down:	
		reg.bottom -= 8;
		bound.top += 8; break;
	case up:
		reg.top += 8;
		bound.bottom -= 8;
		posY -= 8;
		mSprite->SetPosition(posX, posY); 
		break;
	case Direction::none: break;
	default: ;
	}

	
}

RECT BrickNormal::GetBound()
{
	return bound;
}
