#pragma once
#include "Entity.h"

class Bullet:public Entity
{
public:
	Bullet();
	Bullet(int id);
	~Bullet();
	bool isActive = false;
	bool isChange = false;
	RECT GetBound();

	void OnCollision();
	/*void Emplace(Bullet *newBullet);
	bool Compare(Bullet* newBullet);*/

	void Update(float dt) override;
	void SetActive(bool flag);
	void setMoveDirection(Direction direction);
	void Read(InputMemoryBitStream& is) override;
	void Write(OutputMemoryBitStream& os) override;
};


