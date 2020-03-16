#include <fstream>
#include <iostream>
#include "TileMap.h"

TileMap::TileMap(std::string filePath)
{
	LoadLevel(filePath);
}


TileMap::~TileMap()
{
}

void TileMap::LoadLevel(std::string levelToLoad)
{
	//Open File
	std::ifstream inFile;
	inFile.open(levelToLoad);

	if (!inFile.good())
	{
		std::cerr << "Unable To Load Level File" << std::endl;
		return;
	}

	while (!inFile.eof())
	{
		//Read In Int From File
		inFile >> temp;
		//Create Tile Based On Int
		tempVec.push_back(temp);
	}

	for (int i = 0; i < tempVec.size(); i++)
	{
		std::cerr << tempVec[i] <<std::endl;
	}

	inFile.close();
}
