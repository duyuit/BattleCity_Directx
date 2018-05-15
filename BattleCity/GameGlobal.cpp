#include "GameGlobal.h"

HINSTANCE GameGlobal::mHInstance = NULL;
HWND GameGlobal::mHwnd = NULL;
LPD3DXSPRITE GameGlobal::mSpriteHandler = NULL;
int GameGlobal::mWidth = 1300;
int GameGlobal::mHeight = 770;
LPDIRECT3DDEVICE9 GameGlobal::mDevice = nullptr;
bool GameGlobal::isGameRunning = true;
IDirect3DSurface9* GameGlobal::backSurface = nullptr;
TCPSocketPtr GameGlobal::socket = NULL;
int GameGlobal::RTT = 0;
LPDIRECT3DTEXTURE9 GameGlobal::mMapTexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mTankTexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mBoxTexture = NULL;
GameGlobal::GameGlobal()
{
	if(mSpriteHandler)
	{
		mSpriteHandler->GetDevice(&GameGlobal::mDevice);
		D3DXCreateTextureFromFileExA(
			mDevice,
			"Resource files/tileset.png",
			160,
			176,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 0, 255),
			NULL,
			NULL,
			&mMapTexture);

		D3DXCreateTextureFromFileExA(
			mDevice,
			"Resource files/tank.png",
			615,
			615,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 0, 255),
			NULL,
			NULL,
			&mTankTexture);

		D3DXCreateTextureFromFileExA(
			mDevice,
			"Resource files/box.png",
			99,
			48,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 0, 255),
			NULL,
			NULL,
			&mBoxTexture);
	}
}


GameGlobal::~GameGlobal()
{
}

void GameGlobal::SetCurrentDevice(LPDIRECT3DDEVICE9 device)
{
	mDevice = device;
}

LPDIRECT3DDEVICE9 GameGlobal::GetCurrentDevice()
{
	return mDevice;
}

HINSTANCE GameGlobal::GetCurrentHINSTACE()
{
	return mHInstance;
}

HWND GameGlobal::getCurrentHWND()
{
	return mHwnd;
}

void GameGlobal::SetCurrentHINSTACE(HINSTANCE hInstance)
{
	mHInstance = hInstance;
}

void GameGlobal::SetCurrentHWND(HWND hWnd)
{
	mHwnd = hWnd;
}

void GameGlobal::SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	mSpriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::GetCurrentSpriteHandler()
{
	return mSpriteHandler;
}

void GameGlobal::SetWidth(int width)
{
	mWidth = width;
}

int GameGlobal::GetWidth()
{
	return mWidth;
}

void GameGlobal::SetHeight(int height)
{
	mHeight = height;
}

int GameGlobal::GetHeight()
{
	return mHeight;
}