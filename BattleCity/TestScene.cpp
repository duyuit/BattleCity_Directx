#include "TestScene.h"

TestScene::TestScene()
{
	LoadContent();
}

void TestScene::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);

	/*mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera->SetPosition(0, 0);*/
	//set position
	mPlayer = new Player();
	mPlayer->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
}

void TestScene::Update(float dt)
{
	mPlayer->HandleKeyboard(keys);
	mPlayer->Update(dt);
}

void TestScene::Draw()
{
	mPlayer->Draw();
}

void TestScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
}

void TestScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}

