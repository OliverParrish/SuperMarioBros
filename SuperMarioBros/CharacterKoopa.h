#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Character.h"
class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* LevelMap, Vector2D startPosition, float speed, FACING direction);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();

	bool IsInjured() { return mInjured; }

	void Update(float deltaTime, SDL_Event e);
	void Render();
	void Flip();

private:

	bool mInjured;
	float mInjuredTime;
};

