#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;

	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;

	delete mPowBlock;
	mPowBlock = nullptr;

}
void GameScreenLevel1::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	//Draw the Player
	mario->Render();
	luigi->Render();

	// Render pow block
	mPowBlock->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	UpdatePowBlock();

	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		std::cout << "Big Collision Time" << std::endl;
	}

	// Screen Shake
	if (mScreenshake)
	{
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		// End screen shake after set duration
		if (mScreenShakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "failed to load background texture!";
		return false;
	}

	SetLevelMap();
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mario = new CharacterMario(mRenderer, "Images/MarioSpriteSheet.png", mLevelMap, Vector2D(64, 330));
	luigi = new CharacterLuigi(mRenderer, "Images/LuigiSpriteSheet.png", mLevelMap, Vector2D(364, 330));

	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear up any old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}
	//Set up new Map
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenshake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}

void GameScreenLevel1::UpdatePowBlock()
{
	// Check if Mario collided with pow block
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		// Check if the pow block is available
		if (mPowBlock->IsAvailable())
		{
			// See if mario is jumper
			if (mario->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				mario->CancelJump();
			}
		}
	}
	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		// Check if the pow block is available
		if (mPowBlock->IsAvailable())
		{
			// See if mario is jumper
			if (luigi->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				luigi->CancelJump();
			}
		}
	}
}
