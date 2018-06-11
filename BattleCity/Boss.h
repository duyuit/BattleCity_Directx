#pragma once
#include "Entity.h"
class Boss:public Entity
{
public:
	Boss(int ID, D3DXVECTOR2 pos);
	int mHP = 10;
	bool isDelete = false;
	Sprite* m_sprite;
	void Draw();
	void Read(InputMemoryBitStream &is) override;
	void Update(float dt) override;
	~Boss();
};

