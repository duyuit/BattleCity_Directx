#pragma once
#include "Entity.h"

class Brick : public Entity
{
public:
	~Brick();

	virtual void Update();
	bool isNeedToSend = false;
	
	void OnSetPosition(D3DXVECTOR3 position);

	virtual void BeCollideWith_Bullet(D3DXVECTOR2 BulletVelocity);
	void Write(OutputMemoryBitStream& os) override;
	void setDelete(bool deleted);
	bool getDelete();
protected:
	Brick();
	bool Init(D3DXVECTOR3 position);

	virtual const char* FileName() = 0;
	virtual RECT rect() = 0;
	RECT reg;
	bool isDelete;
};

