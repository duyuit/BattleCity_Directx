#pragma once

#include <vector>
#include "Bullet.h"

enum Action
{
	Idle,
	GoLeft,
	GoRight,
	GoUp,
	GoDown,
	Fight
};
class PlayerServer: public Entity
{
public:
	PlayerServer();
	PlayerServer(int ID);
	~PlayerServer();
	void CollideWith_World();
	int ID_currentBullet = 0;
	Action mAction=Idle;
	Action mLastAction = Idle;
	int id_of_bullet = 10;
	int last_move_time = 0;
	void OnChangeAction(Action action);
	RECT GetBound() override;
	void Up_ID_OfBullet();
	void Emplace(PlayerServer* pl);
	void Write(OutputMemoryBitStream& os) override;
	void Read(InputMemoryBitStream& is) override;
	void onHandleKeyboard(int Action);
	void Update(float dt) override;
private:

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void IDLE();
};
 
