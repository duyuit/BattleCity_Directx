#pragma once
#include "Scene.h"

class SceneManager
{
public:
	static SceneManager *GetInstance();
	~SceneManager();
	Scene* GetCurrentScene();
	void Update(float dt);
	void ReplaceScene(Scene *scene);

private:
	SceneManager();
	static SceneManager     *mInstace;
	Scene                   *mCurrentScene;
};

