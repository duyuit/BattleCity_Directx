#include "Player.h"
#include "GameLog.h"


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
	
	vector<RECT> list;
	RECT a;
	a.left = 0; a.right = a.left + 39; a.top = 111; a.bottom = a.top + 42; list.push_back(a);
	a.left = 39; a.right = a.left + 40; a.top = 111; a.bottom = a.top + 40; list.push_back(a);
	shield = new Animation("Resource files/Somethings.png", list, 0.05f, D3DXCOLOR(255, 0, 255, 255));
	vector<RECT> list1;
	a.left = 0; a.right = a.left + 30; a.top = 0; a.bottom = a.top + 30; list1.push_back(a);
	a.left = 30; a.right = a.left + 30; a.top = 0; a.bottom = a.top + 30; list1.push_back(a);
	a.left = 60; a.right = a.left + 34; a.top = 0; a.bottom = a.top + 31; list1.push_back(a);
	a.left = 93; a.right = a.left + 35; a.top = 0; a.bottom = a.top + 32; list1.push_back(a);
	spawn = new Animation("Resource files/Somethings.png", list1, 0.05f, D3DXCOLOR(255, 0, 255, 255));
}

Player::~Player(){}
void Player::Write(OutputMemoryBitStream& os)
{
	Entity::Write(os);
	os.Write((int)mAction, Define::bitofID);
	
}

void Player::OnsetLevel(int m_level)
{
	if (m_level == 2)
	{
		switch (ID)
		{
		case 1:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 2,192,34,192 + 36 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 76,196,76 + 37,196 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 156,195,156 + 31,195 + 34 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 233,195,233 + 36,195 + 30 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;
		case 2:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,192,310+32,192 + 36 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 384,196,384 + 37,196 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,195,464 + 31,195 + 34 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,195,540 + 36,195 + 30 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;
		case 3:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 2,500,34,500 + 36 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 76,504,76 + 37,504 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 156,502,156 + 31,502 + 34 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 233,502,233 + 36,502 + 30 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;
		case 4:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,500,310 + 32,500 + 36 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 384,504,384 + 37,504 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,502,464 + 31,502 + 34 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,502,540 + 36,502 + 30 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;

		}
	}else if(m_level==3)
	{
		switch (ID)
		{
		case 1:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 2,77,34,77 + 37 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 77,79,77 + 37,79 + 31 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 156,78,156 + 31,78 + 37 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 233,79,233 + 36,79 + 31 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;
		case 2:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,77,310+32,77 + 37 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 384,79,384 + 37,79 + 31 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,78,464 + 31,78 + 37 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,79,540 + 36,79 + 31 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;
		case 3:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 2,384,34,384 + 37 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 77,387,77 + 37,387 + 31 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 156,387,156 + 31,387 + 37 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 233,387,233 + 36,387 + 31 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;
		case 4:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,384,310 + 32,384 + 37 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 384,387,384 + 37,387 + 31 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,387,464 + 31,387 + 37 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,387,540 + 36,387 + 31 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;

		}
	}
	else
	{
		switch (ID)
		{
		case 1:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 2,4,2 + 32,4 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 82,2,82 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 156,2,156 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 233,2,233 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255));
			break;
		case 2:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,4,310 + 32,4 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 389,2,389 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,2,464 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,2,540 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;
		case 3:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 2,312,2 + 32,312 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 82,310,82 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 156,310,156 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 233,310,233 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;
		case 4:
			mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,312,310 + 32,312 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 389,310,389 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,310,464 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,310,540 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
			break;

		}
	}
}


void Player::Read(InputMemoryBitStream& is)
{
	last_position = GetPosition();

	Entity::Read(is);
	int action = 0;
	is.Read(action, Define::bitofID);

	int level = 0;
	is.Read(level, Define::bitofTypePacket);
	if(level!=mLevel)
	{
		mLevel = level;
		OnsetLevel(mLevel);
	}
	mAction = (Action)action;
	is.Read(is_protect);
	last_mHeal = mHeal;
	is.Read(mHeal, Define::bitofTypePacket);
	
	is.Read(last_move_time);
	//is.Read(mScore, Define::bitofID);

	mScore_send = 0;
	is.Read(mScore_send, Define::bitofID);
	mScore += mScore_send;
	int x = 0; int y = 0;
	is.Read(x, Define::bitofLocation);
	is.Read(y, Define::bitofLocation);
	position_score.x = x; position_score.y = y;
	


}
void Player::Update(float dt)
{
	if(mHeal!=0 && last_mHeal==0)
	{
		SetSpawn();
	}
	if (mHeal == 0 && !isDelete)
	{
		last_time_die = GetTickCount();
		isDelete = true;
	}

	if (isDelete) {
		if (GetTickCount() - last_time_die > 4000) isDelete = false;
		return;
	}

	if (is_respaw)
	{
		spawn->Update(dt);
		if (GetTickCount() - last_time_spawn > 2000) is_respaw = false;
		return;
	}
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

	if (is_protect) shield->Update(dt);

	
	
}
void Player::HandleKeyboard(std::map<int, bool> keys)
{
	if (isDelete) return;
	if (is_respaw) return;
	
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
	
	int time_to_fight = 1000;
	if (keys[VK_SPACE])
	{
		if (mLevel > 2)
			time_to_fight = 700;
		if (GetTickCount() - lastFire > time_to_fight)
		{
			mAction = Fight;
			lastFire = GetTickCount();
		}
	}

	

	if(mLastAction!=mAction)
	{
	
		OutputMemoryBitStream os;
		os.Write(Define::InputPacket, Define::bitofTypePacket);
		os.Write(ID, Define::bitofID);
		os.Write((int)mAction, Define::bitofID);
		int time_of_packet = GetTickCount();
		os.Write(time_of_packet);
		GameGlobal::socket->Send(os.GetBufferPtr(), os.GetByteLength());
	}
		
	mLastAction = mAction;
	
	
}
void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (isDelete) return;
	if (is_respaw)
	{
		spawn->SetPosition(GetPosition());
		spawn->Draw();
		return;
	}

	mCurrentSprite->SetPosition(this->GetPosition());
	
	mCurrentSprite->Draw(D3DXVECTOR3(posX, posY, 0));
	if (isMe)
	{
		m_top_sprite->SetPosition(D3DXVECTOR3(posX, posY + 35, 0));
		m_top_sprite->Draw();
	}

	if(is_protect)
	{
		shield->SetPosition(GetPosition());
		shield->Draw();
	}
}

void Player::CollideWith_World()
{
	this->vx = 0;
	this->vy = 0;
}


bool Player::Check_to_create_anim()
{
	if (mHeal == 0 && last_mHeal != 0)
		return true;
	return false;
}

void Player::ActiveShield()
{

}

void Player::SetSpawn()
{
	is_respaw = true;
	last_time_spawn = GetTickCount();
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

void Player::CollisionWith(Entity* en)
{

}

void Player::onSetID(int ID)
{
	this->ID = ID;
	switch (ID)
	{
	case 2:
		mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,4,310 + 32,4 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255),GameGlobal::mTankTexture);
		mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 389,2,389 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255),GameGlobal::mTankTexture);
		mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,2,464 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,2,540 + 32,2 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		break;
	case 3:
		mUpSprite = new Sprite("Resource files/tank.png", RECT{ 2,312,2 + 32,312 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 82,310,82 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		mDownSprite = new Sprite("Resource files/tank.png", RECT{ 156,310,156 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		mRightSprite = new Sprite("Resource files/tank.png", RECT{ 233,310,233 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		break;
	case 4:
		mUpSprite = new Sprite("Resource files/tank.png", RECT{ 310,312,310 + 32,312 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 389,310,389 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		mDownSprite = new Sprite("Resource files/tank.png", RECT{ 464,310,464 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		mRightSprite = new Sprite("Resource files/tank.png", RECT{ 540,310,540 + 32,310 + 32 }, 0, 0, D3DXCOLOR(255, 0, 255, 255), GameGlobal::mTankTexture);
		break;

	}
	mCurrentSprite = mUpSprite;
}


void Player::MoveLeft() {

	mCurrentSprite = mLeftSprite;

	if(mLevel>1)
	this->SetVx(-Define::PLAYER_SPEED);
	else 	this->SetVx(-250);

	this->SetVy(0);
	this->mAction = GoLeft;
}
void Player::MoveRight() {

	mCurrentSprite = mRightSprite;

	if (mLevel>1)
	this->SetVx(Define::PLAYER_SPEED);
	else 	this->SetVx(250);


	this->SetVy(0);
	this->mAction = GoRight;
}
void Player::MoveUp() {
	
	mCurrentSprite = mUpSprite;
	if (mLevel>1)
		this->SetVy(250);          
	else
	this->SetVy(Define::PLAYER_SPEED);

	this->SetVx(0);
	this->mAction = GoUp;
}
void Player::MoveDown() {
	
	mCurrentSprite = mDownSprite;
	if (mLevel>1)
		this->SetVy(-250);
	else this->SetVy(-200);
	this->SetVx(0);
	this->mAction = GoDown;
}
void Player::Stand() {
	this->SetVx(0);
	this->SetVy(0);
	this->mAction = Idle;
}