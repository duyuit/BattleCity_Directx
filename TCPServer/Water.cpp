#include "Water.h"



Water::Water(D3DXVECTOR3 position)
{
	Init(position);
	Tag = EntityTypes::Water;
}

const char* Water::FileName() {
	return "Resource files/MapObject.png";
}

RECT Water::rect() {
	reg.left = 0;
	reg.right = this->GetWidth();
	reg.top = 64;
	reg.bottom = 64 + this->GetHeight();

	return reg;
}
Water::~Water()
{
}
