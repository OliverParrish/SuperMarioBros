#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "SoundManager.h"
#include "Collisions.h"
#include "PowBlock.h"


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;

	if (SetUpLevel())
	{
		soundmanager::SoundManager::getInstance()->stopMusic();
		soundmanager::SoundManager::getInstance()->playMusic("Music/Mario.wav");
	}
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

	mEnemies.clear();

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

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime);

	UpdatePowBlock();

	//Player Collision... Not Needed?
	/*if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		std::cout << "Big Collision Time" << std::endl;
	}*/

	// Screen Shake
	if (mScreenshake)
	{
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		// damage the enemies
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			mEnemies[i]->TakeDamage();
		}

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
	
	//create Koopas
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, 75.0f);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, 75.0f);

	//create Coins
	CreateCoin(Vector2D(210, 64));
	CreateCoin(Vector2D(245, 64));
	CreateCoin(Vector2D(275, 64));


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

				soundmanager::SoundManager::getInstance()->playFX("SFX/PowBlock.wav");
			}
		}
	}
	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		// Check if the pow block is available
		if (mPowBlock->IsAvailable())
		{
			// See if luigi is jumper
			if (luigi->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				luigi->CancelJump();

				soundmanager::SoundManager::getInstance()->playFX("SFX/PowBlock.wav");
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	//Only update enemies if any are in the vector
	if (!mEnemies.empty())
	{
		enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//check if enemy is off the screen left and right
			if (mEnemies[i]->GetPosition().x < (float(-mEnemies[i]->GetCollisionBox().width* 0.5f)))
			{
				mEnemies[i]->SetPosition(Vector2D(mEnemies[i]->GetPosition().x + 15, mEnemies[i]->GetPosition().y));
				mEnemies[i]->Flip();
			}
			else if (mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
			{
				mEnemies[i]->SetPosition(Vector2D(mEnemies[i]->GetPosition().x - 15, mEnemies[i]->GetPosition().y));
				mEnemies[i]->Flip();
			}

			//run the enemeies update function
			mEnemies[i]->Update(deltaTime, e);

			//collision with the player
			bool collided = false;

			if (Collisions::Instance()->Circle(Circle2D(mEnemies[i]->GetCollisionRadius(), mEnemies[i]->GetPosition()),Circle2D(mario->GetCollisionRadius(), mario->GetPosition())))
			{
				collided = true;
			}

			if (Collisions::Instance()->Circle(Circle2D(mEnemies[i]->GetCollisionRadius(), mEnemies[i]->GetPosition()), Circle2D(luigi->GetCollisionRadius(), luigi->GetPosition())))
			{
				collided = true;
			}

			if (collided)
			{
				//check if enemies is injured
				if (mEnemies[i]->IsInjured())
				{
					mEnemies[i]->SetAlive(false);
				}
			}

			//check if enemy is dead, if so, set for delete
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}

		}
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
		
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D pos, FACING direction, float speed)
{
	mEnemies.push_back(new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, pos, speed, direction));
}

void GameScreenLevel1::UpdateCoins(float deltaTime)
{
	if (!mCoins.empty())
	{
		coinIndexToDelete = -1;
		
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			mCoins[i]->Update(deltaTime);

			bool collided = false;

			if (Collisions::Instance()->Circle(Circle2D(mCoins[i]->GetCollisionRadius(),mCoins[i]->GetPosition()),Circle2D(mario->GetCollisionRadius(),mario->GetPosition())))
			{
				collided = true;
			}

			if (Collisions::Instance()->Circle(Circle2D(mCoins[i]->GetCollisionRadius(), mCoins[i]->GetPosition()), Circle2D(luigi->GetCollisionRadius(), luigi->GetPosition())))
			{
				collided = true;
			}

			if (collided)
			{
				coinIndexToDelete = i;
				soundmanager::SoundManager::getInstance()->playFX("SFX/Coins.wav");
			}
		}

		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateCoin(Vector2D pos)
{
	mCoins.push_back(new Coin(mRenderer, "Images/Coins.png", pos));
}
