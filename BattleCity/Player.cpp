#include "Player.h"
#include "GameDefine.h"
#include <string>
#include "MemoryBitStream.h"

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
	Dir = MoveDirection::IDLE;

	m_top_sprite = new Sprite("Resource files/topOfplayer.png", RECT(), 0, 0, D3DXCOLOR(255, 0, 255,255));
	
}

Player::~Player(){}

void Player::Update(float dt)
{

	lastPosition = GetPosition();
	if(Dir!=LastDir)
	switch (Dir)
	{
	case Left:
		mCurrentSprite = mLeftSprite;
		this->SetVx(-Define::PLAYER_SPEED);
		this->SetVy(0);
		break;
	case Right: 	
		mCurrentSprite = mRightSprite;
		this->SetVx(Define::PLAYER_SPEED);
		this->SetVy(0);
		break;
	case Up:
		mCurrentSprite = mUpSprite;
		this->SetVy(Define::PLAYER_SPEED);
		this->SetVx(0);
		break;
	case Down:
		mCurrentSprite = mDownSprite;
		this->SetVy(-Define::PLAYER_SPEED);
		this->SetVx(0); 
		break;
	case IDLE:
		this->SetVx(0);
		this->SetVy(0); 
		break;
	default: ;
	}
	Entity::Update(dt);
	LastDir = Dir;
	for(auto bullet:mBullet)
	{
		if (!bullet->isActive) continue;
		bullet->Update(dt);
		
		
	}
	
	
}
void Player::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_SPACE]) {
		if (GetTickCount() - lastFire >= 300)
		{
			for (auto bullet : mBullet)
			{
				if (!bullet->isActive)
				{
					bullet->isActive = true;
					bullet->SetPosition(this->GetPosition());
					if(mCurrentSprite==mUpSprite) bullet->setMoveDirection(Up);
					else if (mCurrentSprite == mLeftSprite) bullet->setMoveDirection(Left);
					else if (mCurrentSprite == mRightSprite) bullet->setMoveDirection(Right);
					else if (mCurrentSprite == mDownSprite) bullet->setMoveDirection(Down);
					lastFire = GetTickCount();
					OutputMemoryBitStream os;
					os.Write(Define::InfoPacket, Define::bitofTypePacket);
					Entity* temp = new Entity();
					temp->ID = bullet->ID;
					temp->Tag = EntityTypes::bullet;
					temp->Dir = bullet->Dir;
					temp->SetPosition(bullet->GetPosition());
					os.Write(temp);
					GameGlobal::socket->Send(os.GetBufferPtr(), os.GetByteLength());
					break;
				}
			}
		}
	}
	if (keys[VK_LEFT]) {
		if (Dir == Left) return;
		MoveLeft();
	}
	else if (keys[VK_RIGHT]) {
		if (Dir == Right) return;
		MoveRight();
	}
	else if (keys[VK_DOWN]) {
		if (Dir == Down) return;
		MoveDown();
	}
	else if (keys[VK_UP]) {
		if (Dir == Up) return;
		MoveUp();
	}
	else {
		if (Dir == IDLE) return;
		Stand();
	}
	
}
void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentSprite->SetPosition(this->GetPosition());
	for (auto bullet : mBullet)
	{
		bullet->Draw();
	}
	mCurrentSprite->Draw(D3DXVECTOR3(posX, posY, 0));
	if (isMe)
	{
		m_top_sprite->SetPosition(D3DXVECTOR3(posX, posY + 35, 0));
		m_top_sprite->Draw();
	}
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
	for (int i = 1; i<4; i++)
	{
		Bullet* bullet = new Bullet(Up);
		bullet->SetPosition(0, 0);
		bullet->ID = this->ID * 10 + i;
		bullet->isActive = false;
		mBullet.push_back(bullet);
	}
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

Entity::MoveDirection Player::getMoveDirection()
{
	return Dir;
}
void Player::setMoveDirection(MoveDirection direction) {
	Dir = direction;
}
void Player::MoveLeft() {
	Stand();
	mCurrentSprite = mLeftSprite;
	Dir = MoveDirection::Left;
}
void Player::MoveRight() {
	Stand();
	mCurrentSprite = mRightSprite;
	Dir = MoveDirection::Right;
}
void Player::MoveUp() {
	Stand();
	mCurrentSprite = mUpSprite;
	
	Dir = MoveDirection::Up;
}
void Player::MoveDown() {
	Stand();
	mCurrentSprite = mDownSprite;
	
	Dir = MoveDirection::Down;
}
void Player::Stand() {
	Dir= MoveDirection::IDLE;
	
}