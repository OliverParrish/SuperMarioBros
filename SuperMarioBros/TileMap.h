#pragma once
#include "SDL.h"
#include "Tile.h"
#include <vector>
#include "Coin.h"
#include "Flag.h"
#include "CharacterKoopa.h"

class TileMap
{
public:

	TileMap(SDL_Renderer* renderer);
	~TileMap();

	void Render();

	void GenerateTileMap(char** map, int rows, int columns);

	Tile* GetTileAt(int x, int y);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

	std::vector<std::vector<Tile*>>* mTiles;

	std::vector<Coin*> mCoins;

	std::vector<CharacterKoopa*> mKoopa;
	
	Flag* mFlag;


private:

	SDL_Renderer* mRenderer;

	int mWidth;
	int mHeight;

	char** mMap;
};

