#pragma once
#include "Scene.h"
#include "Player.h"
#include "GameMap.h"

class TestTiepScene : public Scene
{
public:
	TestTiepScene();
	~TestTiepScene();
	void CheckCollision(float dt);
	void Update(float dt);
	void Draw();
	Player* mpl;
	GameMap* map;
	
};


