#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>
#include "Scene.h"
#include "Animation.h"
#include "Camera.h"
#include <map>
#include "Player.h"


class TestScene : public Scene
{
public:
	TestScene();
	void Update(float dt);
	void LoadContent();
	void Draw();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
protected:
	Camera *mCamera;
	Player *mPlayer;

	std::map<int, bool> keys;
};

