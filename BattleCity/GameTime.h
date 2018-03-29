#pragma once
#include <Windows.h>

class GameTime
{
public:
	void StartCounter();
	float GetCouter();
	static GameTime* GetInstance();
	~GameTime();

private:
	GameTime();
	LARGE_INTEGER mStartTime, mEndTime, mDelta, mClockRate;
	static GameTime *mInstance;
};

