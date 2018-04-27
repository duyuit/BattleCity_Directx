#pragma once
#include "Entity.h"
#include "Sprite.h"
class Brick : public Entity
{
public:
	~Brick();

	virtual void Update();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void OnSetPosition(D3DXVECTOR3 position);

	virtual void BeCollideWith_Bullet(Direction dir);
	void Read(InputMemoryBitStream& is) override;
	void setDelete(bool deleted);
	bool getDelete();
protected:
	Brick();
	bool Init(D3DXVECTOR3 position);

	virtual const char* FileName() = 0;
	virtual RECT rect() = 0;
	Sprite* mSprite;
	RECT reg;

	bool isDelete;
};

