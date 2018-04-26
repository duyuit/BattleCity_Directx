#include "MetalBrick.h"

MetalBrick::MetalBrick(D3DXVECTOR3 position)
{
	Init(position);
	Tag = EntityTypes::MetalBrick;
}
const char* MetalBrick::FileName() {
	return "Resource files/MapObject.png";
}
RECT MetalBrick::rect() {
	reg.left = 0;
	reg.right = this->GetWidth();
	reg.top = 32;
	reg.bottom = 32 + this->GetHeight();

	return reg;
}
void MetalBrick::BeCollideWith_Bullet(D3DXVECTOR2 BulletVelocity)
{
}
MetalBrick::~MetalBrick()
{
}
