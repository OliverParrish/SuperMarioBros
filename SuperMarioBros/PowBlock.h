#pragma once

#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include <iostream>

class PowBlock
{
private:

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;

	
public:

	PowBlock(SDL_Renderer* sdl_renderer, LevelMap* levelMap);
	~PowBlock();

	void TakeAHit();
	void Render();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; }
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight); }



};
