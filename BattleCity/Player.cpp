#include "Player.h"
#include "GameDefine.h"
#include <string>

Player::Player()
{
	mUpSprite		= new Sprite("Resource files/tank.png", RECT{   0,0, 32,30 });
	mLeftSprite		= new Sprite("Resource files/tank.png", RECT{  64,0, 96,30 });
	mDownSprite		= new Sprite("Resource files/tank.png", RECT{ 128,0,160,30 });
	mRightSprite	= new Sprite("Resource files/tank.png", RECT{ 192,0,224,30 });
	mUpSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	mLeftSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	mDownSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	mRightSprite->SetScale(D3DXVECTOR2(1.5, 1.5));
	this->vx = 0;
	this->vy = 0;
	mCurrentSprite = mUpSprite;
	Dir = MoveDirection::Up;

}

Player::~Player(){}

void Player::Update(float dt)
{

	lastPosition = GetPosition();
	Entity::Update(dt);
	
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
	this->SetVx(-Define::PLAYER_SPEED);
	this->SetVy(0);
	
	Dir = MoveDirection::Left;
}
void Player::MoveRight() {
	Stand();
	mCurrentSprite = mRightSprite;
	this->SetVx(Define::PLAYER_SPEED);
	this->SetVy(0);
	Dir = MoveDirection::Right;
}
void Player::MoveUp() {
	Stand();
	mCurrentSprite = mUpSprite;
	this->SetVy(Define::PLAYER_SPEED);
	this->SetVx(0);
	Dir = MoveDirection::Up;
}
void Player::MoveDown() {
	Stand();
	mCurrentSprite = mDownSprite;
	this->SetVy(-Define::PLAYER_SPEED);
	this->SetVx(0);
	Dir = MoveDirection::Down;
}
void Player::Stand() {
	Dir=IDLE;
	this->SetVx(0);
	this->SetVy(0);
}