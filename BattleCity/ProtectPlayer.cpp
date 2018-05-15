#include "ProtectPlayer.h"



ProtectPlayer::ProtectPlayer(D3DXVECTOR3 Position)
{
	Init(Position);
	Tag = EntityTypes::ProtectPlayerItem;

}

ProtectPlayer::ProtectPlayer()
{
	Tag = EntityTypes::ProtectPlayerItem;
	bound = Entity::GetBound();
}


ProtectPlayer::~ProtectPlayer()
{
}

const char * ProtectPlayer::fileName()
{
	return "Resource files/Somethings.png";
}

RECT ProtectPlayer::rect()
{
	reg.left = 0;
	reg.right = this->GetWidth();
	reg.top = 32;
	reg.bottom = 32 +this->GetHeight();

	return reg;
}

RECT ProtectPlayer::GetBound()
{
	bound = Entity::GetBound();
	return bound;
}
