#include "Entity.h"

Entity::Entity()
{
	Tag = none;
}

D3DXVECTOR2 Entity::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

RECT Entity::GetBound()
{
	RECT bound;

	bound.left = posX - width / 2;
	bound.right = posX + width / 2;
	bound.top = posY - height / 2;
	bound.bottom = posY + height / 2;

	return bound;
}

void Entity::OnSetPosition(D3DXVECTOR2 pos)
{

}

void Entity::Update(float dt)
{
	//velocity = pixel / s
	posX += vx * dt;
	posY += vy * dt;
}

void Entity::SetPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;
}

void Entity::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(pos.x, pos.y);
}


void Entity::AddPosition(D3DXVECTOR2 pos)
{
	this->SetPosition(this->GetPosition() + pos);
}


void Entity::AddPosition(float x, float y)
{
	AddPosition(D3DXVECTOR2(x, y));
}

void Entity::SetWidth(int width)
{
	this->width = width;
}

int Entity::GetWidth()
{
	return width;
}

void Entity::SetHeight(int height)
{
	this->height = height;
}

int Entity::GetHeight()
{
	return height;
}

float Entity::GetVx()
{
	return vx;
}

void Entity::SetVx(float vx)
{
	this->vx = vx;
}

void Entity::AddVx(float vx)
{
	this->vx += vx;
}

float Entity::GetVy()
{
	return vy;
}

void Entity::SetVy(float vy)
{
	this->vy = vy;
}

void Entity::AddVy(float vy)
{
	this->vy += vy;
}
