#include "Brick.h"

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
	this->vx = 0;
	this->vy = 0;
	rect();
	SetPosition(position);
	setDelete(false);
	return true;
}
void Brick::OnSetPosition(D3DXVECTOR3 position) {

}
void Brick::BeCollideWith_Bullet(D3DXVECTOR2 BulletVelocity)
{
}

void Brick::Write(OutputMemoryBitStream& os)
{

	os.Write(Tag, Define::bitofID);
	os.Write(ID, Define::bitofID);
	os.Write((int)dir, Define::bitofID);
}

void Brick::Update()
{
}

Brick::~Brick()
{
}
