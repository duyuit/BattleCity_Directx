#include "Pointed.h"

Pointed::Pointed(int score,D3DXVECTOR2 position)
{
	RECT point;
	switch (score)
	{
	case 100:  point = RECT{ 5,0, 32,14 }; break;
	case 200:	point = RECT{ 37,0, 65,14 }; break;
	case 300:point = RECT{ 70,0, 98,14 }; break;
	case 400:point = RECT{ 103,0,131,14 }; break;
	case 500:point = RECT{ 136,0,164,14 }; break;
	}
	mPoint = new Sprite("Resource files/Point.png", point,0,0,D3DCOLOR_ARGB(255,0,0,1));
	this->position = position;
	timeDelete = 60;
	isDelete = false;
}


Pointed::~Pointed()
{
}

void Pointed::Update()
{
	if (timeDelete <= 0)
		isDelete = true;
	--timeDelete;
}

void Pointed::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (isDelete)
		return;
	mPoint->SetPosition(this->position);
	mPoint->Draw();
}

bool Pointed::getIsDelete()
{
	return isDelete;
}
