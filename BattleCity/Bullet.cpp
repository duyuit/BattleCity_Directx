#include "Bullet.h"
#include "GameDefine.h"
#include "GameLog.h"

Bullet::Bullet()
{
	Tag = Entity::bullet;
	mCurrentSprite = new Sprite("Resource files/Somethings.png", RECT{ 177,14, 177 + 10,14 + 10 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
}

Bullet::Bullet(int id)
{
	Tag = bullet;
	ID = id;
	mCurrentSprite = new Sprite("Resource files/Somethings.png", RECT{ 177,14, 177 + 10,14 + 10 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
}

void Bullet::Update(float dt) {
	if(!isActive) return;
	Entity::Update(dt);

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

void Bullet::Emplace(Bullet* bl)
{
	Entity::Emplace(bl);
	isActive = bl->isActive;

}

void Bullet::setMoveDirection(Direction direction) {
	dir = direction;
	delete mCurrentSprite;
	switch (dir) 
	{
	case Direction::left:  MoveLeft(); break;
	case Direction::right:MoveRight(); break;
	case Direction::up:MoveUp(); break;
	case Direction::down:MoveDown(); break;
	default: ;
	}
}
void Bullet::Read(InputMemoryBitStream& is)
{
	Entity::Read(is);
	is.Read(isActive);
	setMoveDirection(dir);
}

void Bullet::Write(OutputMemoryBitStream& os)
{
	//Entity::Write(os);
	os.Write(isActive);

}


void Bullet::MoveLeft() {

	mCurrentSprite = new Sprite("Resource files/Somethings.png", RECT{ 148,12, 156,20 },  0, 0 ,D3DXCOLOR(255, 0, 255, 255));
	this->SetVx(-Define::BULLET_SPEED);
	this->SetVy(0);
}
void Bullet::MoveRight() {
	mCurrentSprite = new  Sprite("Resource files/Somethings.png", RECT{ 180,12, 188,20 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	this->SetVx(Define::BULLET_SPEED);
	this->SetVy(0);

}
void Bullet::MoveUp() {
	mCurrentSprite = new Sprite("Resource files/Somethings.png", RECT{ 134,12, 140,20 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	this->SetVy(Define::BULLET_SPEED);
	this->SetVx(0);

}
void Bullet::MoveDown() {
	mCurrentSprite = new Sprite("Resource files/Somethings.png", RECT{ 166,12, 172,20 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	this->SetVy(-Define::BULLET_SPEED);
	this->SetVx(0);
}
Bullet::~Bullet()
{
}
