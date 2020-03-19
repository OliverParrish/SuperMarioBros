#include "PowBlock.h"
#include "Commons.h"
#include <string>
#include "LevelMap.h"

PowBlock::PowBlock(SDL_Renderer* sdl_renderer, LevelMap* levelMap)
{
	std::string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(sdl_renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture: " << imagePath << std::endl;
		return;
	}
	mLevelMap = levelMap;

	mSingleSpriteWidth = mTexture->GetWidth() / 3; //3 Sprites on this spritesheet in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);

}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete	mTexture;
	mLevelMap = NULL;
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft--;

	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
	}
}
	

void PowBlock::Render(int camX, int camY)
{
	//get the portion of the sprite sheet you want to draw
	int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(Vector2D(mPosition.x - camX, mPosition.y - camY), &portionOfSpriteSheet, 0.0, nullptr, SDL_FLIP_NONE);
}
