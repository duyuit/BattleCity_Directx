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
		ID_currentBullet++;
		if (ID_currentBullet == ID * 10 + 5)
			ID_currentBullet = ID * 10 + 1;
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
	os.Write(last_move_time);
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
	

}



void PlayerServer::MoveLeft()
{
	dir = left;
	this->SetVx(-200.0f);
	this->SetVy(0);
}

void PlayerServer::MoveRight()
{
	dir = right;
	this->SetVx(200.0f);
	this->SetVy(0);
}

void PlayerServer::MoveUp()
{
	dir = up;
	this->SetVx(0);
	this->SetVy(200.0f);
}

void PlayerServer::MoveDown()
{
	dir = down;
	this->SetVx(0);
	this->SetVy(-200.0f);
}

void PlayerServer::IDLE()
{
	this->SetVx(0);
	this->SetVy(0);
}