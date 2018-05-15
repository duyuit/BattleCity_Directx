#include "PlayerServer.h"
#include "Bullet.h"

PlayerServer::PlayerServer()
{
	this->Tag = Entity::player;
	this->width = 32;
	this->height = 32;
	this->vx = 0;
	this->vy = 0;
	this->Tag = Entity::player;
	ID_currentBullet = ID * 10 + 1;

}

PlayerServer::PlayerServer(int ID)
{
	this->ID = ID;

	this->width = 32;
	this->height = 32;
	this->vx = 0;
	this->vy = 0;
	this->Tag = Entity::player;
	ID_currentBullet = ID * 10+1;
}

PlayerServer::~PlayerServer()
{

}

void PlayerServer::CollideWith_World()
{ 
	this->vx = 0;
	this->vy = 0;
}

void PlayerServer::ActiveShield()
{
	is_protect = true;
	time_start_protect = 0;
}

void PlayerServer::OnChangeAction(Action action)
{
	mAction = action;
	switch (mAction)
	{
	case Idle:  IDLE();  break;
	case GoLeft: MoveLeft(); break;
	case GoRight:MoveRight(); break;
	case GoUp:MoveUp(); break;
	case Action::GoDown:MoveDown(); break;
	case Action::Fight:
	
		break;
	default: break;
	}
	
}

RECT PlayerServer::GetBound()
{
	RECT rect;
	float width = 32 / 2;
	rect.left = this->posX - width;
	rect.right = rect.left + 32;
	rect.top = this->posY -width;
	rect.bottom = rect.top + 32;

	return rect;
}

void PlayerServer::Up_ID_OfBullet()
{
	ID_currentBullet++;
	if (ID_currentBullet == ID * 10 + 5)
		ID_currentBullet = ID * 10 + 1;
}

void PlayerServer::CollisionWith(Entity* en)
{
	if (en->Tag == EntityTypes::UpgradeItem)
	{
		if (mLevel < 3) mLevel++;
	}
	else if (en->Tag == EntityTypes::ProtectPlayerItem)
	{
		ActiveShield();
	}
	else if (en->Tag == EntityTypes::bullet)
	{
		if(!is_protect)
		mHeal--;
	}
}

void PlayerServer::Emplace(PlayerServer* pl)
{
	Entity::Emplace(pl);
	this->mAction = pl->mAction;
	

}

void PlayerServer::Write(OutputMemoryBitStream& os)
{
	Entity::Write(os);
	int a = (int)mAction;
	os.Write(a, Define::bitofID);
	os.Write(mLevel, Define::bitofTypePacket);
	os.Write(is_protect);
	os.Write(last_move_time);
	os.Write(mScore, Define::bitofID);
}



void PlayerServer::Read(InputMemoryBitStream& is)
{
	Entity::Read(is);
	int action = 0;
	is.Read(action, Define::bitofID);
	mAction = (Action)action;
	OnChangeAction(mAction);
}

void PlayerServer::onHandleKeyboard(int action)
{
	mAction = (Action)action;
	OnChangeAction(mAction);

}

 void PlayerServer::Update(float dt)
{
	
	Entity::Update(dt);
	if (is_protect)
		time_start_protect += dt;
	if (time_start_protect > 3) 
		is_protect = false;

}



void PlayerServer::MoveLeft()
{
	dir = left;
	if(mLevel>1)
		this->SetVx(-250.0f);
	else
		this->SetVx(-200.0f);

	this->SetVy(0);
}

void PlayerServer::MoveRight()
{
	dir = right;
	if (mLevel>1)
		this->SetVx(250.0f);
	else
		this->SetVx(200.0f);
	this->SetVy(0);
}

void PlayerServer::MoveUp()
{
	dir = up;
	this->SetVx(0);
	if (mLevel>1)
		this->SetVy(250.0f);
	else
		this->SetVy(200.0f);
	
}

void PlayerServer::MoveDown()
{
	dir = down;
	this->SetVx(0);
	if (mLevel>1)
		this->SetVy(-250.0f);
	else
		this->SetVy(-200.0f);
}

void PlayerServer::IDLE()
{
	this->SetVx(0);
	this->SetVy(0);
}