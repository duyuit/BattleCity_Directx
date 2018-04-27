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
		oldReg = reg;
	}
}

void BrickNormal::BeCollideWith_Bullet(D3DXVECTOR2 BulletVelocity)
{
	isNeedToSend = true;
	if (BulletVelocity.x > 0) {
		reg.left += 8;
		bound.left += 8;
		posX += 8;
		dir = left;

	}
	else if (BulletVelocity.x < 0) {
		reg.right -= 8;
		bound.right -= 8;
		dir = right;
	}
	else if (BulletVelocity.y > 0) {
		reg.bottom -= 8;
		bound.top += 8;
		dir = down;
	}
	else if (BulletVelocity.y < 0) {
		reg.top += 8;
		bound.bottom -= 8;
		posY -= 8;
		dir = up;
	}

}

//void BrickNormal::Write(OutputMemoryBitStream& os)
//{
//
//		os.Write(Tag, Define::bitofID);
//		os.Write(ID, Define::bitofID);
//		os.Write((int)dir, Define::bitofID);
//
//}

RECT BrickNormal::GetBound()
{
	return bound;
}
