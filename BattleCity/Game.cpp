#include "Game.h"
#include "GameGlobal.h"
#include "SceneManager.h"
#include "TestScene.h"
#include "WaitRoomScene.h"
#include "TestTiepScene.h"
#include <thread>
#include "RoomScene.h"


Game::Game(int fps)
{
	mFPS = fps;

	SceneManager::GetInstance()->ReplaceScene(new RoomScene());

	InitLoop();
}
void Game::Update(float dt)
{
	SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
	Render();
}
void Game::Render()
{
	auto device = GameGlobal::GetCurrentDevice();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, scene->GetBackcolor(), 0.0f, 0);

	{
		device->BeginScene();

		//bat dau ve
		GameGlobal::GetCurrentSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		//draw here
		scene->Draw();

		//ket thuc ve
		GameGlobal::GetCurrentSpriteHandler()->End();

		device->EndScene();
	}

	device->Present(0, 0, 0, 0);
}

void ReceivePacket()
{
	while (1)
	{
		SceneManager::GetInstance()->GetCurrentScene()->ReceivePakcet();
	}
}

void Game::InitLoop()
{
	MSG msg;

	//std::thread task_receive_packet(ReceivePacket);
	//task_receive_packet.detach();
	float tickPerFrame = 1.0f / mFPS, delta = 0;

	while (GameGlobal::isGameRunning)
	{
		
		SceneManager::GetInstance()->GetCurrentScene()->ReceivePakcet();
		GameTime::GetInstance()->StartCounter();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	
		
		delta += GameTime::GetInstance()->GetCouter();
		
		if (delta >= tickPerFrame)
		{
		
			Update(1.0f / 60);
			delta = 0;
		}
		else
		{
			int delta_time = tickPerFrame - delta;
			SceneManager::GetInstance()->GetCurrentScene()->ReceivePakcet();
			Sleep(delta_time);
			delta = tickPerFrame;
		}

	}
}
Game::~Game()
{
}
