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
	const int InfoPacket = 4;

	const int bitofTypePacket = 4;
	const int bitofID = 3;
	const int bitofLocation = 12;
}