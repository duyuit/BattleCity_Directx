#include "UpgradeItem.h"



UpgradeItem::UpgradeItem(D3DXVECTOR3 Position)
{
	Init(Position);
	Tag = EntityTypes::UpgradeItem;
	bound = Entity::GetBound();
}

UpgradeItem::UpgradeItem()
{
	Tag = EntityTypes::UpgradeItem;
	bound = Entity::GetBound();
}


UpgradeItem::~UpgradeItem()
{
}

const char * UpgradeItem::fileName()
{
	return "Resource files/Somethings.png";
}

RECT UpgradeItem::rect()
{
	reg.left = 96;
	reg.right = 96+this->GetWidth();
	reg.top = 32;
	reg.bottom = 32 + this->GetHeight();

	return reg;
}

RECT UpgradeItem::GetBound()
{
	bound = Entity::GetBound();
	return bound;
}
