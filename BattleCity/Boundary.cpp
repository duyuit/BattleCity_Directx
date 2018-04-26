#include "Boundary.h"



Boundary::Boundary(D3DXVECTOR3 position)
{
	Init(position);
}

const char* Boundary::FileName() {
	return "Resource files/MapObject.png";
}
RECT Boundary::rect() {
	reg.left = 64;
	reg.right = 64 + this->GetWidth();
	reg.top = 64;
	reg.bottom = 64+this->GetHeight();

	return reg;
}

Boundary::~Boundary()
{
}
