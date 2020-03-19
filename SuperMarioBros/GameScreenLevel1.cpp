#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "SoundManager.h"
#include "Collisions.h"
#include "PowBlock.h"
#include <fstream>
#include "Camera.h"


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;
	//Run sound once level has been set up
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

	delete mCharacterMario;
	mCharacterMario = nullptr;

	delete mCharacterLuigi;
	mCharacterLuigi = nullptr;

	delete mPowBlock;
	mPowBlock = nullptr;

	mEnemies.clear();

}

void GameScreenLevel1::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0 - Camera::GetInstance()->GetPosition().x, mBackgroundYPos), SDL_FLIP_NONE);

	// Render tilemap
	mTileMap->Render();

	//Draw the Player
	mCharacterMario->Render();
	mCharacterLuigi->Render();

	// Render pow block
	mPowBlock->Render(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y);

	//Draw enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y);
	}

	//Draw coins
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y);
	}

	mScoreText->Draw();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Update stuff for movement etc.
	mCharacterMario->Update(deltaTime, e);
	mCharacterLuigi->Update(deltaTime, e);

	//set camera position to center of mario
	Camera::GetInstance()->SetPosition(Vector2D((mCharacterMario->GetPosition().x + 16 / 2) - CAMERA_WIDTH / 2, mBackgroundYPos));

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
	
	//load background Texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "failed to load background texture!";
		return false;
	}

	//create Pow Block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	//create Mario
	mCharacterMario = new CharacterMario(mRenderer, "Images/MarioSpriteSheet.png", mTileMap, Vector2D(64, 330));

	//create Luigi
	mCharacterLuigi = new CharacterLuigi(mRenderer, "Images/LuigiSpriteSheet.png", mTileMap, Vector2D(364, 330));
	
	SetLevelMap();

	//create Koopas
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, 75.0f);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, 75.0f);

	//create Coins
	CreateCoin(Vector2D(210, 64));
	CreateCoin(Vector2D(245, 64));
	CreateCoin(Vector2D(280, 64));
	CreateCoin(Vector2D(280, 32));
	CreateCoin(Vector2D(245, 32));
	CreateCoin(Vector2D(210, 32));

	//Create text score
	score = 0;
	std::string scoreString = "Score: " + std::to_string(score);
	const char* score = scoreString.c_str();

	mScoreText = new FontUI(mRenderer, score, { 255,255,255,0 });
	mScoreText->SetPosition(new Vector2D(16, 16));

	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	


	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int old_map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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
	mLevelMap = new LevelMap(old_map);

	//read file for map
	std::ifstream file("Level1.txt");

	int rows = 0, columns = 0;

	std::string line;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			rows++;
		}


	}
	for (int x = 0; x < line.length(); x++)
	{
		if (line[x] != ' ')
			columns++;
	}

	int** map;

	map = new int* [rows];

	for (unsigned int i = 0; i < rows; i++)
	{
		map[i] = new int[columns];
	}

	//clears file & goes to beginning
	file.clear();
	file.seekg(0, std::ios::beg);

	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < columns; y++)
		{
			file >> map[x][y];
		}
	}
	file.close();

	mTileMap = new TileMap(mRenderer);
	mTileMap->GenerateTileMap(map, rows, columns);
	
	mCharacterMario->mCurrentTileMap = mTileMap;
	mCharacterLuigi->mCurrentTileMap = mTileMap;
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
	if (Collisions::Instance()->Box(mCharacterMario->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		// Check if the pow block is available
		if (mPowBlock->IsAvailable())
		{
			// See if mario is jumper
			if (mCharacterMario->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				mCharacterMario->CancelJump();

				soundmanager::SoundManager::getInstance()->playFX("SFX/PowBlock.wav");
			}
		}
	}
	if (Collisions::Instance()->Box(mCharacterLuigi->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		// Check if the pow block is available
		if (mPowBlock->IsAvailable())
		{
			// See if luigi is jumper
			if (mCharacterLuigi->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				mCharacterLuigi->CancelJump();

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

			if (Collisions::Instance()->Circle(Circle2D(mEnemies[i]->GetCollisionRadius(), mEnemies[i]->GetPosition()),Circle2D(mCharacterMario->GetCollisionRadius(), mCharacterMario->GetPosition())))
			{
				collided = true;
			}

			if (Collisions::Instance()->Circle(Circle2D(mEnemies[i]->GetCollisionRadius(), mEnemies[i]->GetPosition()), Circle2D(mCharacterLuigi->GetCollisionRadius(), mCharacterLuigi->GetPosition())))
			{
				collided = true;
			}

			if (collided)
			{
				//check if enemies is injured
				if (mEnemies[i]->IsInjured())
				{
					mEnemies[i]->SetAlive(false);
					AddScore(100);
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
	mEnemies.push_back(new CharacterKoopa(mRenderer, "Images/Koopa.png", mTileMap, pos, speed, direction));
}

void GameScreenLevel1::UpdateCoins(float deltaTime)
{
	//check if coin has been collected
	if (!mCoins.empty())
	{
		coinIndexToDelete = -1;
		
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			mCoins[i]->Update(deltaTime);

			bool collided = false;

			if (Collisions::Instance()->Circle(Circle2D(mCoins[i]->GetCollisionRadius(),mCoins[i]->GetPosition()),Circle2D(mCharacterMario->GetCollisionRadius(),mCharacterMario->GetPosition())))
			{
				collided = true;
			}

			if (Collisions::Instance()->Circle(Circle2D(mCoins[i]->GetCollisionRadius(), mCoins[i]->GetPosition()), Circle2D(mCharacterLuigi->GetCollisionRadius(), mCharacterLuigi->GetPosition())))
			{
				collided = true;
			}

			if (collided)
			{
				//play coin sound
				coinIndexToDelete = i;
				soundmanager::SoundManager::getInstance()->playFX("SFX/Coins.wav");

				//add score for collecting coin
				AddScore(50);
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

void GameScreenLevel1::AddScore(int add)
{
	score += add;

	if (mScoreText != nullptr)
	{
		std::string scoreString = "Score: " + std::to_string(score);
		const char* score = scoreString.c_str();
		mScoreText->SetText(score);

		mScoreText->UpdateSurface();
		mScoreText->UpdateTexture();
	}
}
