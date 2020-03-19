#pragma once
#include "SDL.h"
#include "Tile.h"
#include <vector>

class TileMap
{
public:

	TileMap(SDL_Renderer* renderer);
	~TileMap();

	void Render();

	void GenerateTileMap(int** map, int rows, int columns);

	Tile* GetTileAt(int x, int y);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

	std::vector<std::vector<Tile*>>* mTiles;


private:

	SDL_Renderer* mRenderer;

	int mWidth;
	int mHeight;

	int** mMap;
};

