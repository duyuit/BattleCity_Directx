#include "Bullet.h"
#include "GameDefine.h"

Bullet::Bullet(MoveDirection direction)
{
	Tag = Entity::bullet;
	mUpSprite		= new Sprite("Resource files/Somethings.png", RECT{ 160,14, 160+10,14+10 },0,0, D3DXCOLOR(255, 0, 255, 255));
	mLeftSprite		= new Sprite("Resource files/Somethings.png", RECT{ 177,14, 177+10,14+10}, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	mDownSprite		= new Sprite("Resource files/Somethings.png", RECT{ 199,14, 199+10,14+10 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	mRightSprite	= new Sprite("Resource files/Somethings.png", RECT{ 215,14, 215+10,14+10 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));

	if (direction == MoveDirection::Left)
		MoveLeft();
	else if (direction == MoveDirection::Right)
		MoveRight();
	else if (direction == MoveDirection::Up)
		MoveUp();
	else if (direction == MoveDirection::Down)
		MoveDown();

}
void Bullet::Update(float dt) {
	if(!isActive) return;
	Entity::Update(dt);
	if (GetPosition().x > GameGlobal::GetWidth() ||GetPosition().x <0 ||
		GetPosition().y > GameGlobal::GetHeight() || GetPosition().y <0)
	{
		isActive = false;
		SetPosition(0, 0);
	}
}
void Bullet::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (!isActive) return;
	mCurrentSprite->SetPosition(this->GetPosition());
	mCurrentSprite->Draw(D3DXVECTOR3(posX, posY, 0));
}
RECT Bullet::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentSprite->GetWidth() / 2;
	rect.right = rect.left + mCurrentSprite->GetWidth();
	rect.top = this->posY - mCurrentSprite->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentSprite->GetHeight();

	return rect;
}
Entity::MoveDirection Bullet::getMoveDirection()
{
	return Dir;
}
void Bullet::setMoveDirection(MoveDirection direction) {
	Dir = direction;
	if (Dir == MoveDirection::Left)
		MoveLeft();
	else if (Dir == MoveDirection::Right)
		MoveRight();
	else if (Dir == MoveDirection::Up)
		MoveUp();
	else if (Dir == MoveDirection::Down)
		MoveDown();
}
void Bullet::MoveLeft() {
	mCurrentSprite = mLeftSprite;
	this->SetVx(-Define::BULLET_SPEED);
	this->SetVy(0);
	Dir = MoveDirection::Left;
}
void Bullet::MoveRight() {
	mCurrentSprite = mRightSprite;
	this->SetVx(Define::BULLET_SPEED);
	this->SetVy(0);
	Dir = MoveDirection::Right;
}
void Bullet::MoveUp() {
	mCurrentSprite = mUpSprite;
	this->SetVy(Define::BULLET_SPEED);
	this->SetVx(0);
	Dir = MoveDirection::Up;
}
void Bullet::MoveDown() {
	mCurrentSprite = mDownSprite;
	this->SetVy(-Define::BULLET_SPEED);
	this->SetVx(0);
	Dir = MoveDirection::Down;
}
Bullet::~Bullet()
{
}
