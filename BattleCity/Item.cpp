#include "Item.h"

Item::Item()
{
	
	isDelete = false;
	exist_time =7;

}

bool Item::Init(D3DXVECTOR3 position)
{
	Entity::SetWidth(32);
	Entity::SetHeight(32);

	mSprite = new Sprite(fileName(), rect(),0,0, D3DXCOLOR(255, 0, 255, 255));
	SetPosition(position);
	mSprite->SetPosition(position);
	mSprite->SetSourceRect(reg);
	return true;
}


Item::~Item()
{
}

void Item::Update(float dt)
{
	cout_time += dt;
	if (cout_time >= exist_time) isDelete = true;
}
int time_nhap_nhay = 0;
void Item::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if(exist_time - cout_time < 2)
	{
		time_nhap_nhay++;
		if(time_nhap_nhay==5)
		{
			mSprite->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
			time_nhap_nhay = 0;
		}
	}else mSprite->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);

}

void Item::OnSetPosition(D3DXVECTOR3 position)
{
	mSprite->SetPosition(position);
}

void Item::BeCollideWith_Player()
{
	isDelete = true;
}

void Item::Read(InputMemoryBitStream& is)
{
	Entity::Read(is);
	Init(D3DXVECTOR3(posX, posY, 0));
}

bool Item::getDelete()
{
	return isDelete;
}
