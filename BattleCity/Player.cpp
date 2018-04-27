#include "Player.h"


Player::Player()
{
	mUpSprite = new Sprite("Resource files/tank.png", RECT{ 2,4,2+ 32,4+ 32 },0,0, D3DXCOLOR(255, 0, 255, 255));
	mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 82,2,82+32,2+32 },0,0, D3DXCOLOR(255, 0, 255, 255));
	mDownSprite = new Sprite("Resource files/tank.png", RECT{ 156,2,156+32,2+32 },0,0, D3DXCOLOR(255, 0, 255, 255));
	mRightSprite = new Sprite("Resource files/tank.png", RECT{ 233,2,233+32,2+32}, 0, 0, D3DXCOLOR(255, 0, 255, 255));
	/*mUpSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	mLeftSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	mDownSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	mRightSprite->SetScale(D3DXVECTOR2(1.5, 1.5));*/
	this->vx = 0;
	this->vy = 0;

	Tag = Entity::player;
	mCurrentSprite = mUpSprite;
	mAction = Idle;

	m_top_sprite = new Sprite("Resource files/topOfplayer.png", RECT(), 0, 0, D3DXCOLOR(255, 0, 255,255));
	
}

Player::~Player(){}
void Player::Write(OutputMemoryBitStream& os)
{
	Entity::Write(os);
	os.Write((int)mAction, Define::bitofID);
	
}



void Player::Read(InputMemoryBitStream& is)
{
	Entity::Read(is);
	int action = 0;
	is.Read(action, Define::bitofID);
	//mAction = (Action)action;
	is.Read(last_move_time);
}
void Player::Update(float dt)
{


	Entity::Update(dt);
	switch (dir) {
	case Direction::left:mCurrentSprite = mLeftSprite; break;
	case Direction::right:mCurrentSprite = mRightSprite; break;
	case up:mCurrentSprite = mUpSprite; break;
	case down:mCurrentSprite = mDownSprite; break;
	default: ;
	}
	switch (mAction)
	{
	case Idle:  Stand();  break;
	case GoLeft: MoveLeft(); break;
	case GoRight:MoveRight(); break;
	case GoUp:MoveUp(); break;
	case GoDown:MoveDown(); break;
	case Action::Fight:break;
	default: break;
	}


	
	
}
void Player::HandleKeyboard(std::map<int, bool> keys,int &check_to_send)
{
	
	if (keys[VK_LEFT]) {
		if (mAction != GoLeft)
		MoveLeft();
	}
	else if (keys[VK_RIGHT]) {
		if (mAction != GoRight)
		MoveRight();
	}
	else if (keys[VK_DOWN]) {
		if (mAction != GoDown)
		MoveDown();
	}
	else if (keys[VK_UP]) {
		if (mAction != GoUp)
		MoveUp();
	}
	else {
		if (mAction != Idle)
		Stand();
	}
	

	if (keys[VK_SPACE])
	{
		if (GetTickCount() - lastFire >= 300)
		{
			mAction = Fight;
			lastFire = GetTickCount();
		}
	}

	

	//if(mLastAction!=mAction)
	//{
		OutputMemoryBitStream os;
		os.Write(Define::InputPacket, Define::bitofTypePacket);
		os.Write(ID, Define::bitofID);
		os.Write((int)mAction, Define::bitofID);
		int time_of_packet = GetTickCount();
		os.Write(time_of_packet);
		GameGlobal::socket->Send(os.GetBufferPtr(), os.GetByteLength());

	//}
		
	mLastAction = mAction;
	
	
}
void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentSprite->SetPosition(this->GetPosition());
	
	mCurrentSprite->Draw(D3DXVECTOR3(posX, posY, 0));
	if (isMe)
	{
		m_top_sprite->SetPosition(D3DXVECTOR3(posX, posY + 35, 0));
		m_top_sprite->Draw();
	}
}

void Player::CollideWith_World()
{
	this->vx = 0;
	this->vy = 0;
}


void Player::Emplace(Player* pl)
{
	Entity::Emplace(pl);
	this->mAction = pl->mAction;

}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentSprite->GetWidth() / 2;
	rect.right = rect.left + mCurrentSprite->GetWidth();
	rect.top = this->posY - mCurrentSprite->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentSprite->GetHeight();
	return rect;
}

void Player::onSetID(int ID)
{
	this->ID = ID;
	/*for (int i = 1; i<4; i++)
	{
		Bullet* bullet = new Bullet(Up);
		bullet->SetPosition(0, 0);
		bullet->ID = this->ID * 10 + i;
		bullet->isActive = false;
		mBullet.push_back(bullet);
	}*/
	switch (ID)
	{
	case 2:
		mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,4,310 + 32,4 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 389,2,389 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,2,464 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,2,540 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		break;
	case 3:
		mUpSprite = new Sprite("Resource files/tank.png", RECT{ 2,312,2 + 32,312 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 82,310,82 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		mDownSprite = new Sprite("Resource files/tank.png", RECT{ 156,310,156 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		mRightSprite = new Sprite("Resource files/tank.png", RECT{ 233,310,233 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		break;
	case 4:
		mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,312,310 + 32,312 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 389,310,389 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,310,464 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,310,540 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
		break;

	}
	mCurrentSprite = mUpSprite;
}

//Entity::MoveDirection Player::getMoveDirection()
//{
//	return Dir;
//}
//void Player::setMoveDirection(MoveDirection direction) {
//	Dir = direction;
//}
void Player::MoveLeft() {

	mCurrentSprite = mLeftSprite;
	this->SetVx(-Define::PLAYER_SPEED);
	this->SetVy(0);
	this->mAction = GoLeft;
}
void Player::MoveRight() {

	mCurrentSprite = mRightSprite;
	this->SetVx(Define::PLAYER_SPEED);
	this->SetVy(0);
	this->mAction = GoRight;
}
void Player::MoveUp() {
	
	mCurrentSprite = mUpSprite;
	this->SetVy(Define::PLAYER_SPEED);
	this->SetVx(0);
	this->mAction = GoUp;
}
void Player::MoveDown() {
	
	mCurrentSprite = mDownSprite;
	this->SetVy(-Define::PLAYER_SPEED);
	this->SetVx(0);
	this->mAction = GoDown;
}
void Player::Stand() {
	this->SetVx(0);
	this->SetVy(0);
	this->mAction = Idle;
}