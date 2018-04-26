#include "Bullet.h"
 Bullet::Bullet()
{
	 Tag = bullet;
}

Bullet::Bullet(int id)
{
	Tag = bullet;
	ID = id;
}

Bullet::~Bullet()
{
}

//void Bullet::Emplace(Bullet* newBullet)
//{
//	this->ID = newBullet->ID;
//	this->SetPosition(newBullet->GetPosition());
//	this->isActive = newBullet->isActive;
//	this->dir = newBullet->dir;
//}
//
//bool Bullet::Compare(Bullet* newBullet)
//{
//	if (this->GetPosition() != newBullet->GetPosition() || isActive != newBullet->isActive || dir != newBullet->dir) return false;
//	return true;
//}

RECT Bullet::GetBound()
{
	
		RECT rect;
		rect.left = this->posX - 6 / 2;
		rect.right = rect.left + 6;
		rect.top = this->posY - 6/ 2;
		rect.bottom = rect.top + 6;
		return rect;
	
}

void Bullet::Update(float dt)
{
	
	 if (isActive)
		 Entity::Update(dt);
	 if (posY < 0 || posY>1000 || posX < 0 || posX>1000)
		 SetActive(false);
	 

}

void Bullet::SetActive(bool flag)
{
	lastActive = isActive;
	isActive = flag;
}

void Bullet::setMoveDirection(Direction direction)
{
	dir = direction;
	switch (direction) 
	{
		case left: this->vx = -400; this->vy = 0;  break;
		case right: this->vx = 400; this->vy = 0; break;
		case up:this->vx = 0; this->vy = 400;  break;
		case down: this->vx = 0; this->vy = -400; break;
		default: ;
	}
}

void Bullet::Read(InputMemoryBitStream& is)
{

	Entity::Read(is);
	is.Read(isActive);

}

void Bullet::Write(OutputMemoryBitStream& os)
{
	Entity::Write(os);
	os.Write(isActive);
}