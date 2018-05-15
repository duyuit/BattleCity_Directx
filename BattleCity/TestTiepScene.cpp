#include "TestTiepScene.h"



TestTiepScene::TestTiepScene()
{
	mpl = new Player();
	mpl->SetPosition(200, 200);
	mpl->mAction = Action::GoRight;
	mpl->onSetID(1);

	
	map= new GameMap("Resource files/map.tmx");
	
}


TestTiepScene::~TestTiepScene()
{
}

void TestTiepScene::CheckCollision(float dt)
{
	vector<Brick*> listCollision = map->GetListBrick();
	for (size_t i = 0; i < listCollision.size(); i++) {
		if (GameCollision::isCollide(mpl, listCollision[i], dt))
			mpl->CollideWith_World();
	}
}

void TestTiepScene::Update(float dt)
{
	CheckCollision(dt);
	mpl->Update(dt);
	//map->Update(dt);
}

void TestTiepScene::Draw()
{
	
	map->Draw();
	mpl->Draw();
}
