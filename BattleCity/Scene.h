#pragma once

#include "GameGlobal.h"

class Scene
{
public:
	virtual void Update(float dt);
	virtual void LoadContent();
	virtual void Draw();

	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);

	D3DCOLOR GetBackcolor();

	~Scene();

protected:
	Scene();

	D3DCOLOR                mBackColor;

};

