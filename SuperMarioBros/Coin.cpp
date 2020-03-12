#include "Coin.h"
#include <iostream>



Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);

	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cerr << "Could not load coin image from " << imagePath << std::endl;
	}
	mPosition = startPosition;

	mFrame = 1;
	mFrameCount = 3;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();

	mCollisionRadius = 20.0f;
}


Coin::~Coin()
{
	delete mRenderer;
	mRenderer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Coin::Render()
{
	int left = mSingleSpriteWidth * (mFrame - 1);

	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}

void Coin::Update(float deltaTime)
{
	mCurFrameTime += deltaTime * 10;

	if (mCurFrameTime > 2)
	{
		mFrame++;

		if (mFrame > mFrameCount)
		{
			mFrame = 1;
		}

		mCurFrameTime = 0;
	}
}
