#pragma once
#include "Scene.h"
#include "Player.h"
#include "GameMap.h"
#include "Label.h"

class TestTiepScene : public Scene
{
public:
	TestTiepScene();
	~TestTiepScene();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode); 
	std::map<int, bool> keys;
	void CheckCollision(float dt);
	void Update(float dt);
	void Draw();
	Player* mpl;
	GameMap* map;
	Label FPS;
};


