#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"	
#include "MapReader\Tmx.h.in"
#include "GameGlobal.h"
#include "Brick.h"
#include "BrickNormal.h"
#include "MetalBrick.h"
#include "Water.h"
#include "Boundary.h"
#include "GameCollision.h"
#include "GameDebugDraw.h"

class GameMap
{
public:
	GameMap(char* filePath);
	void Update(float dt);
	void Draw();
	Tmx::Map* GetMap();
	RECT GetWorldMapBound();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	std::vector<Brick*> GetListBrick();
	void eraseBrick(int i);
	~GameMap();
private:
	void LoadMap(char* filePath);
	bool isContain(RECT rect1, RECT rect2);
	GameDebugDraw *mDebugDraw;
	Tmx::Map                *mMap;
	std::map<int, Sprite*>  mListTileset;
	std::vector<Brick*> mListBrick;

};

