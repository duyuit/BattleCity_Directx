#pragma once
#include "Sprite.h"
namespace GIVEPOINT {
	const RECT ONE_HUNDRED		= RECT{   5,0, 32,14 };
	const RECT TWO_HUNDRED		= RECT{  37,0, 65,14 };
	const RECT THREE_HUNDRED	= RECT{  70,0, 98,14 };
	const RECT FOUR_HUNDRED		= RECT{ 103,0,131,14 };
	const RECT FIVE_HUNDRED		= RECT{ 136,0,164,14 };
}
class Pointed
{
public:
	Pointed(int score,D3DXVECTOR2);
	~Pointed();

	void Update();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	bool getIsDelete();
private:
	D3DXVECTOR2 position;
	Sprite * mPoint;
	bool isDelete;
	int timeDelete;
};

