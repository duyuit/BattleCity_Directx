// TCPServer.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <conio.h>

#include <string>


#include <ctime>
#include "NetWorkManager.h"
#include "GameTime.h"
#pragma comment(lib,"WS2_32")





int main()
{
	srand(time(NULL));
	NetWorkManager* net_work = new NetWorkManager();
	float current_time = 0;
	float tickPerFrame = 1.0f / 60, delta = 0;
	MSG msg;
	while (1)
	{
		/*float delta = (GetTickCount() - current_time)/1000.0f;

		if(delta >= tickPerFrame)
		{
			current_time = GetTickCount();
			net_work->Update(delta);
		}*/
		
		
		GameTime::GetInstance()->StartCounter();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
 		delta += GameTime::GetInstance()->GetCouter();
		
		if (delta >= tickPerFrame)
		{
			net_work->Update(delta);
			delta = 0;
		}
		else
		{
			int delta_time = tickPerFrame - delta;
			Sleep(delta_time);
			delta = tickPerFrame;
		}

	}
	
	
	return 0;
}


