#include "Player.h"
#include "GameDefine.h"
#include <string>

Player::Player()
{
	mUpSprite		= new Sprite("Resource files/tank.png", RECT{   0,0, 32,30 });
	mLeftSprite		= new Sprite("Resource files/tank.png", RECT{  64,0, 96,30 });
	mDownSprite		= new Sprite("Resource files/tank.png", RECT{ 128,0,160,30 });
	mRightSprite	= new Sprite("Resource files/tank.png", RECT{ 192,0,224,30 });
	/*mUpSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	mLeftSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	mDownSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	mRightSprite->SetScale(D3DXVECTOR2(1.5, 1.5));*/
	this->vx = 0;
	this->vy = 0;

	mCurrentSprite = mUpSprite;
	Dir = MoveDirection::IDLE;

	m_top_sprite = new Sprite("Resource files/topOfplayer.png", RECT(), 0, 0, D3DXCOLOR(255, 0, 255,255));
	//m_top_sprite->SetScale(D3DXVECTOR2(0.5, 0.5));
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
	
}
void Player::HandleKeyboard(std::map<int, bool> keys)
{
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
	switch (ID)
	{
	case 2:
		mUpSprite = new Sprite("Resource files/tank.png", RECT{ 257,3,257+ 28,3+28 });
		mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 323,2, 323+28,2+28 });
		mDownSprite = new Sprite("Resource files/tank.png", RECT{ 386,2,386+28,28 });
		mRightSprite = new Sprite("Resource files/tank.png", RECT{ 449,2,449+28,2+28 });
		break;
	case 3:
		mUpSprite = new Sprite("Resource files/tank.png", RECT{ 1,259,1 + 28,259 + 28 });
		mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 67,257, 67 + 28,257 + 28 });
		mDownSprite = new Sprite("Resource files/tank.png", RECT{ 129,257,129 + 28,257+28 });
		mRightSprite = new Sprite("Resource files/tank.png", RECT{ 194,257,194 + 28,257 + 28 });
		break;
	case 4:
		mUpSprite = new Sprite("Resource files/tank.png", RECT{ 257,260,257 + 28,260 + 28 });
		mLeftSprite = new Sprite("Resource files/tank.png", RECT{ 323,257, 323 + 28,257 + 28 });
		mDownSprite = new Sprite("Resource files/tank.png", RECT{ 386,258,386 + 28,258 + 28 });
		mRightSprite = new Sprite("Resource files/tank.png", RECT{ 449,258,449 + 28,258 + 28 });
		break;

	}
	mCurrentSprite = mUpSprite;
}

MoveDirection Player::getMoveDirection()
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