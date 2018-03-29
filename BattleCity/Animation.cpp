#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(const char* filePath, int totalFrame,int rows,int columns, int startRow, int startColumn, int endRow, int endColumn, float timePerFrame, D3DCOLOR colorKey)
{
	InitWithAnimation(filePath, totalFrame,rows,columns, startRow, startColumn, endRow, endColumn, timePerFrame, colorKey);
}

void Animation::InitWithAnimation(const char* filePath, int totalFrame, int rows, int columns, int startRow, int startColumn, int endRow, int endColumn, float timePerFrame, D3DCOLOR colorKey)
{
	//GAMELOG("animation: frame: %d, row: %d, column: %d, time: %f", totalFrame, rows, columns, timePerFrame);
	this->InitWithSprite(filePath);
	mTimePerFrame = timePerFrame;
	mTotalFrame = totalFrame;
	mRows = rows;
	mColumns = columns;
	mStartRow = startRow;
	mStartColumn = startColumn;
	mEndRow = endRow;
	mEndColumn = endColumn;
	mCurrentColumn = mStartColumn;
	mCurrentRow = mStartRow;
	//width - height luc nay la cua spritesheet
	mFrameWidth = GetWidth() / mColumns;
	mFrameHeight = GetHeight() / mRows;

	SetWidth(mFrameWidth);
	SetHeight(mFrameHeight);

	mRect.top = 0;
	mRect.left = 0;
	mRect.right = mFrameWidth;
	mRect.bottom = mFrameHeight;
	SetSourceRect(mRect);
}

Animation::~Animation(){}

void Animation::Update(float dt)
{
	if (mTotalFrame <= 1)
		return;
	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime = 0;
		mCurrentIndex++;
		mCurrentColumn++;

		if (mCurrentIndex >= mTotalFrame)
		{
			mCurrentIndex = 0;
			mCurrentColumn = mStartColumn;
			mCurrentRow = mStartRow;
		}

		if (mCurrentColumn >= mEndColumn)
		{
			mCurrentColumn = mStartColumn;
			mCurrentRow++;

			if (mCurrentRow >= mEndRow)
				mCurrentRow = mStartRow;
		}

		mRect.left = mCurrentColumn * mFrameWidth;
		mRect.right = mRect.left + mFrameWidth;
		mRect.top = mCurrentRow * mFrameHeight;
		mRect.bottom = mRect.top + mFrameHeight;

		SetSourceRect(mRect);
	}
	else
	{
		mCurrentTotalTime += dt;
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