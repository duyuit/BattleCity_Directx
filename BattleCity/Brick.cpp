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
	Entity::SetWidth(32);
	Entity::SetHeight(32);
	mSprite = new Sprite(FileName(), rect());
	SetPosition(position);
	mSprite->SetPosition(position);
	return true;
}
void Brick::OnSetPosition(D3DXVECTOR3 position) {
	mSprite->SetPosition(position);
}
void Brick::BeCollideWith_Bullet(D3DXVECTOR2 BulletVelocity)
{
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
