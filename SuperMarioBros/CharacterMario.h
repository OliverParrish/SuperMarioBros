#pragma once
#include "Character.h"


class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, TileMap* LevelMap, Vector2D startPosition);
	~CharacterMario();

	 void Render();
	void Update(float deltaTime, SDL_Event e);

};
