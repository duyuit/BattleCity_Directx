#pragma once
#include "GameGlobal.h"
#include "MemoryBitStream.h"
#include "Sprite.h"
class Player;
enum Direction
{
	left,
	right,
	up,
	down,
	none
};
class Entity
{
public:
	virtual ~Entity() = default;
	Entity();

	

	enum EntityTypes
	{
		player, bullet, item, block, none, Brick,
		MetalBrick,
		Water,
		ProtectPlayerItem,
		UpgradeItem
	};
	int ID = 0;
	Direction dir = up;

	EntityTypes Tag=none; //Tag de nhan vien loai Entity

	virtual void Write(OutputMemoryBitStream &os);
	virtual void Read(InputMemoryBitStream &is);
	virtual void Emplace(Entity* en);

	bool isDelete = false;

	EntityTypes getTag();

	virtual RECT GetBound();

	virtual void SetPosition(float x, float y);

	virtual void SetPosition(D3DXVECTOR2 pos);

	virtual void SetPosition(D3DXVECTOR3 pos);


	virtual void AddPosition(D3DXVECTOR2 pos);

	virtual void AddPosition(float x, float y);

	virtual void SetWidth(int width);

	virtual int GetWidth();

	virtual void SetHeight(int height);

	virtual int GetHeight();

	virtual float GetVx();

	virtual void SetVx(float vx);

	virtual void AddVx(float vx);

	virtual float GetVy();

	virtual void SetVy(float vy);

	virtual void AddVy(float vy);

	virtual D3DXVECTOR2 GetPosition();
	virtual void Update(float dt);
	virtual void CollisionWith(Entity* en);
protected:

	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(D3DXVECTOR3 pos);

	//vi tri tam position x va y
	float posX, posY;

	//phan toc vx, vy
	float vx, vy;

	//size cua entity
	float width, height;

};

