#pragma once
#include "Sprite.h"
#include <vector>

using namespace std;

class Animation : public Sprite
{
public:
	//ham ho tro lay animation voi anh co duy nhat 1 hang
	Animation(const char* filePath,  vector<RECT> sourcefloat, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	Animation();

	virtual void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void SetCurrentTotalTime(float time);
	~Animation();
	vector<RECT> mSourceRect;
	int GetCurrentFrame();
protected:
	//su dung cho ke thua
	
	int 
		mCurrentIndex, //gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
		mTotalFrame;  //tong so frame


	float mTimePerFrame, //thoi gian luan chuyen 1 frame
		mCurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe

	RECT                        mRect;
};


