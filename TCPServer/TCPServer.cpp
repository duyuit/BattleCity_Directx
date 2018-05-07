// TCPServer.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <conio.h>

#include <string>


#include <ctime>
#include "NetWorkManager.h"
#include "GameTime.h"
#include <thread>

#pragma comment(lib,"WS2_32")




void Receive_thread(NetWorkManager* net)
{
	while (1)
	{
		net->ReceivePacket();
	}

}
int main()
{
	srand(time(NULL));
	NetWorkManager* net_work = new NetWorkManager();
	GameTime *_gameTime = new GameTime();
	_gameTime->init();
	float _detalTime = 0;
	float _lastTime = 0;

	const float tickPerFrame = 1.0f / 60;
	
	int temp = 0, temp1 = 0;

	MSG msg;
	std::thread task_receive_packet(Receive_thread, net_work);
	task_receive_packet.detach();
	while (1)
	{
		//net_work->ReceivePacket();
		net_work->Handle_Packet();
	
			_gameTime->update();
			_detalTime = _gameTime->getTotalTime() - _lastTime;

			if (_detalTime >= tickPerFrame)
			{
				_lastTime += tickPerFrame;
				net_work->Update(_detalTime);
				temp++;
				if (temp == 60)
				{
					temp1++;
					temp = 0;
					printf("%i\t%f\n",temp1,_detalTime);
				}
			}
			else
			{
				Sleep((tickPerFrame - _detalTime) * 1000.0f);
			}
	
		
	}
	
	
	return 0;
}


//_gameTime->update();
//
//_detalTime = _gameTime->getTotalTime() - _lastTime;
//net_work->ReceivePacket();
//
//GameTime::GetInstance()->StartCounter();
//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//{
//	TranslateMessage(&msg);
//	DispatchMessage(&msg);
//}
//delta += GameTime::GetInstance()->GetCouter();
//
//if (delta >= tickPerFrame)
//{
//	net_work->Update(delta);
//	delta = 0;
//}
//else
//{
//	int delta_time = tickPerFrame - delta;
//	Sleep(delta_time);
//	delta = tickPerFrame;
//}