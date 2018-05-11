#include "Water.h"



Water::Water(D3DXVECTOR3 position)
{
	Init(position);
	Tag = EntityTypes::Water;
}



RECT Water::rect() {
	reg.left = 0;
	reg.right = this->GetWidth();
	reg.top = 160;
	reg.bottom = 160 + this->GetHeight();

	return reg;
}
Water::~Water()
{
}
