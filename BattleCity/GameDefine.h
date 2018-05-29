#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
namespace Define {
	const float PLAYER_SPEED = 200.0f;
	const float FRAME_PER_SECOUND = 0.15f;
	const double PI = M_PI;
	const float BULLET_SPEED = 500.0f;

	const int WelcomePacket = 1;
	const int UpdateCountPlayer = 2;
	const int LetStart = 3;
	const int TankPacket = 4;
	const int WorldStatePacket = 5;
	const int InputPacket = 6;
	const int RequestName = 7;
	const int ChooseRoom =8;
	const int ExitGame = 9;
	const int CreateRoom = 10; 
	const int GameOver = 11;
	const int OutRoom = 12;

	const int bitofTypePacket = 4;
	const int bitofID = 11;
	const int bitofLocation = 12;
}