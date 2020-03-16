#pragma once
#include <vector>
#include "Tile.h"

class TileMap
{
public:
	TileMap(std::string filePath);
	~TileMap();

	void LoadLevel(std::string levelToLoad);
	int temp;
	std::vector<int> tempVec;
};

