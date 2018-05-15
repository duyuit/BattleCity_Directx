#pragma once
#include "Entity.h"
#include "Sprite.h"
class Item : public Entity
{
public:
	~Item();

	virtual void Update(float dt);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void OnSetPosition(D3DXVECTOR3 position);
	void BeCollideWith_Player();
	void Read(InputMemoryBitStream& is) override;
	bool getDelete();
protected:
	Item();
	bool Init(D3DXVECTOR3 position);

	float exist_time = 0;
	float cout_time = 0;

	virtual const char* fileName() = 0;
	virtual RECT rect() = 0;
	Sprite* mSprite;
	RECT reg;
	bool isDelete;
};

