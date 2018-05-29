#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(const char* filePath, vector<RECT> source, float timePerFrame, D3DCOLOR colorKey )
{
	
	this->InitWithSprite(filePath,source.at(0),0,0,colorKey);
	mTimePerFrame = timePerFrame;
	mTotalFrame = source.size();
	mSourceRect = source;

	mRect = source.at(0);
	SetSourceRect(mRect);
}


Animation::~Animation()
{
	mTexture->Release();
}

int Animation::GetCurrentFrame()
{
	return mCurrentIndex;
}

void Animation::Update(float dt)
{
	if (mTotalFrame <= 1)
		return;
	if (mCurrentIndex <= mTotalFrame)
	{
		
		if (mTotalFrame <= 1)
			return;
		if (mCurrentIndex <= mTotalFrame)
		{

			mRect =mSourceRect.at(mCurrentIndex) ;
		}
		if (mCurrentTotalTime >= mTimePerFrame)
		{
			mCurrentTotalTime = 0;
			mCurrentIndex++;


			if (mCurrentIndex >= mTotalFrame)
				mCurrentIndex = 0;

		}
		else
		{
			mCurrentTotalTime += dt;
		}
	

		SetSourceRect(mRect);
		
	}

}
void Animation::SetCurrentTotalTime(float time) {
	mCurrentTotalTime = time;
}
void Animation::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale,
	D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	Sprite::Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}