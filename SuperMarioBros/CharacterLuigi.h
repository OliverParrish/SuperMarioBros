#pragma once
#include "Character.h"


class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, TileMap* LevelMap, Vector2D startPosition);
	~CharacterLuigi();

	void Render();
	void Update(float deltaTime, SDL_Event e);

};
