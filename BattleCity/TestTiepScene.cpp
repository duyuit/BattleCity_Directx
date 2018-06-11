#include "TestTiepScene.h"


TestTiepScene::TestTiepScene()
{
	mpl = new Player();
	mpl->SetPosition(200, 200);
	mpl->mAction = Action::GoRight;
	mpl->onSetID(1);
	FPS = Label("", 30, 10, D3DXVECTOR2(GameGlobal::GetWidth() - 100, GameGlobal::GetHeight() - 100));
	
	map= new GameMap("Resource files/map.tmx");
	
}


TestTiepScene::~TestTiepScene()
{
}

void TestTiepScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
}

void TestTiepScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
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
//	mpl->HandleKeyboard(keys);
	CheckCollision(dt);
	mpl->Update(dt);
	//map->Update(dt);
}

void TestTiepScene::Draw()
{
	
	map->Draw();
	mpl->Draw();
	FPS.Draw(std::to_string(GameGlobal::fps));
}
