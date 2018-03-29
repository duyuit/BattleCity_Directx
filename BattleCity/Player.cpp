#include "Player.h"
#include "GameDefine.h"
#include <string>

Player::Player()
{
	mSprite = new Sprite("Resource files/tank.png", RECT{ 0,0,30,30 });
	this->vx = 0;
	this->vy = 0;
	Dir = MoveDirection::Up;
}

Player::~Player(){}

void Player::Update(float dt)
{

	Entity::Update(dt);
	//OutputDebugStringA("\n");
	//OutputDebugStringA(std::to_string(GetPosition().y).c_str());
}
void Player::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT]) {
		if (Dir == Left) return;
		OutputDebugStringA("\n");
		OutputDebugStringA(std::to_string(this->posY - mSprite->GetHeight() / 2).c_str());
		OutputDebugStringA("\t");
		OutputDebugStringA(std::to_string(this->posY + mSprite->GetHeight() / 2).c_str());
		OutputDebugStringA("\t");
		OutputDebugStringA(std::to_string(this->posY).c_str());
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
		OutputDebugStringA("\n");
		OutputDebugStringA(std::to_string(this->posY - mSprite->GetHeight() / 2).c_str());
		OutputDebugStringA("\t");
		OutputDebugStringA(std::to_string(this->posY + mSprite->GetHeight() / 2).c_str());
		OutputDebugStringA("\t");
		OutputDebugStringA(std::to_string(this->posY).c_str());
		Stand();
	}
}
void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mSprite->SetPosition(this->GetPosition());

	mSprite->Draw(D3DXVECTOR3(posX, posY, 0));
}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = this->posX - mSprite->GetWidth() / 2;
	rect.right = rect.left + mSprite->GetWidth();
	rect.top = this->posY - mSprite->GetHeight() / 2;
	rect.bottom = rect.top + mSprite->GetHeight();

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
	mSprite->SetRotation(-90);// quay trai
	this->SetVx(-Define::PLAYER_SPEED);
	this->SetVy(0);
	
	Dir = MoveDirection::Left;
}
void Player::MoveRight() {
	Stand();
	mSprite->SetRotation(90);
	this->SetVx(Define::PLAYER_SPEED);
	this->SetVy(0);
	Dir = MoveDirection::Right;
}
void Player::MoveUp() {
	Stand();
	mSprite->SetRotation(0);
	this->SetVy(-Define::PLAYER_SPEED);
	this->SetVx(0);
	Dir = MoveDirection::Up;
}
void Player::MoveDown() {
	Stand();
	mSprite->SetRotation(180);
	this->SetVy(Define::PLAYER_SPEED);
	this->SetVx(0);
	Dir = MoveDirection::Down;
}
void Player::Stand() {
	Dir = IDLE;
	this->SetVx(0);
	this->SetVy(0);
}