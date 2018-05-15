#include "Brick.h"
#include "GameGlobal.h"
void Brick::setDelete(bool deleted)
{
	isDelete = deleted;
}
bool Brick::getDelete()
{
	return isDelete;
}
Brick::Brick()
{
	isDelete = false;
}

bool Brick::Init(D3DXVECTOR3 position) {
	Entity::SetWidth(16);
	Entity::SetHeight(16);
	mSprite = new Sprite("Resource files/tileset.png", rect(),0,16,16,GameGlobal::mMapTexture);
	SetPosition(position);
	mSprite->SetPosition(position);
	return true;
}
void Brick::OnSetPosition(D3DXVECTOR3 position) {
	mSprite->SetPosition(position);
}

void Brick::BeCollideWith_Bullet()
{
	
}



void Brick::Read(InputMemoryBitStream& is)
{
	
	is.Read(isDelete);
}



void Brick::Update()
{
}

void Brick::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mSprite->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

Brick::~Brick()
{
}
