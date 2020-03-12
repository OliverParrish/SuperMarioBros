#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"

class Coin
{
public:

	Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Coin();

	void Render();
	void Update(float deltaTime);

	Vector2D GetPosition() { return mPosition; }

	float GetCollisionRadius() { return mCollisionRadius; }
private:

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	float mCollisionRadius;

	float mCurFrameTime;
	int mFrame;
	int mFrameCount;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

};

