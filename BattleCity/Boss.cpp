#include "Boss.h"






Boss::Boss(int ID,D3DXVECTOR2 pos)
{
	this->Entity::SetPosition(pos);
	this->ID = ID;
	switch (ID)
	{
	case 1:
		m_sprite= new Sprite("Resource files/boss.png", RECT{0,0,50,50}, 50, 50, D3DXCOLOR(255, 0, 255, 255));
		break;
	case 2:
		m_sprite = new Sprite("Resource files/boss.png", RECT{ 50,0,100,50 }, 50, 50, D3DXCOLOR(255, 0, 255, 255)); 
		break;
	case 3:
		m_sprite = new Sprite("Resource files/boss.png", RECT{ 0,50,50,100 }, 50, 50, D3DXCOLOR(255, 0, 255, 255));
		break;
	case 4:
		m_sprite = new Sprite("Resource files/boss.png", RECT{ 50,50,100,100 }, 50, 50, D3DXCOLOR(255, 0, 255, 255)); 
		break;
	}
	width = 50;
	height = 50;
	Tag = boss;
}

void Boss::Draw()
{
	if (isDelete) return;
	m_sprite->SetPosition(GetPosition());
	m_sprite->Draw();
}

void Boss::Read(InputMemoryBitStream& is)
{
	is.Read(mHP, Define::bitofTypePacket);
	if (mHP == 0)
		isDelete = true;
}

void Boss::Update(float dt)
{

}

Boss::~Boss()
{
}
