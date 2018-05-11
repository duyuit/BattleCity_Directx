#include "Boundary.h"



Boundary::Boundary(D3DXVECTOR3 position)
{
	Init(position);
}


RECT Boundary::rect() {
	reg.left = 32;
	reg.right = 32 + this->GetWidth();
	reg.top = 144;
	reg.bottom = 144 +this->GetHeight();

	return reg;
}

Boundary::~Boundary()
{
}
