#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "SoundManager.h"
#include "Collisions.h"
#include "TileMap.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, TileMap* map)
{
	//Renderer for the texture of characters
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);

	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "could not load character Image file" << std::endl;
	}

	mAlive = true;

	//Start position Renderer
	mPosition = startPosition;

	mCurrentTileMap = map;

	mFacingDirection = FACING_RIGHT;

	mMovingLeft = false;
	mMovingRight = false;
	mJumping = false;
	mCurFrame = 1;

	mCollisionRadius = 15.0f;
}

Character::~Character()
{
	delete mRenderer;
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void Character::Render(int camX, int camY)
{
	if (!mAlive) return;
	//get position of sprite sheet
	int left = mSingleSpriteWidth * (mCurFrame - 1);
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(Vector2D(mPosition.x - camX, mPosition.y - camY), &portionOfSpriteSheet, 0.0, nullptr, SDL_FLIP_NONE);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(Vector2D(mPosition.x - camX, mPosition.y - camY), &portionOfSpriteSheet, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (!mAlive) return;
	if (mPosition.y > 450)
	{
		mAlive = false;
	}

	int centralXPosition = (int)(mPosition.x + (mSingleSpriteWidth * 0.5f)) / TILE_WIDTH;
	int centralYPosition = (int)(mPosition.y + (mSingleSpriteHeight * 0.5f)) / TILE_WIDTH;
	int headPosition = (int)(mPosition.y) / 32;
	int footPosition = (int)(mPosition.y + mSingleSpriteHeight) / TILE_HEIGHT;

	int rightSidePosition = (int)(mPosition.x + mSingleSpriteWidth) / 32;
	int leftSidePosition = (int)(mPosition.x) / 32;

	mCanMove = true;

	// Only update if there is a tilemap
	if (mCurrentTileMap != nullptr)
	{
		// If there is no tile, assume we are in air
		if (mCurrentTileMap->GetTileAt(centralXPosition, footPosition) == nullptr)
		{
			AddGravity(deltaTime);
		}
		else
		{
			mCanJump = true;
		}
		if (mCurrentTileMap->GetTileAt(centralXPosition, headPosition) != nullptr)
		{
			if (mCurrentTileMap->GetTileAt(centralXPosition, headPosition)->GetCollisionType() == CollisionType::SOLID)
			{
				if (mJumping)
				{
					mJumping = false;
				}
				mPosition.y += 5;
			}
		}

		//collision left and right
		if (mFacingDirection == FACING::FACING_RIGHT)
		{
			if (mCurrentTileMap->GetTileAt(rightSidePosition, centralYPosition) != nullptr)
			{
				if (mCurrentTileMap->GetTileAt(rightSidePosition, centralYPosition)->GetCollisionType() == CollisionType::SOLID)
				{
						mCanMove = false;
						mPosition = Vector2D(mPosition.x - 1, mPosition.y);
						
				}
			}
		}
		else if (mFacingDirection == FACING::FACING_LEFT)
		{
			if (mCurrentTileMap->GetTileAt(leftSidePosition, centralYPosition) != nullptr)
			{
				if (mCurrentTileMap->GetTileAt(leftSidePosition, centralYPosition)->GetCollisionType() == CollisionType::SOLID)
				{
					mCanMove = false;
					mPosition = Vector2D(mPosition.x + 1, mPosition.y);

				}
			}
		}
	}

	//character animation
	UpdateFrame(deltaTime);

	//Jumping for Characters
	if (mJumping)
	{
		mPosition.y -= mJumpForce * deltaTime;


		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}

	//Control movement
	if (mCanMove)
	{
		if (mMovingLeft)
		{
			MoveLeft(deltaTime);
		}
		else if (mMovingRight)
		{
			MoveRight(deltaTime);
		}

	}

	
}

void Character::UpdateFrame(float deltaTime)
{
	//jump movement
	if (IsJumping() || !mCanJump)
	{
		mCurFrame = mJumpFrame;
	}
	else if (mMovingRight || mMovingLeft)
	{
		mCurFrameTime += deltaTime * 10;

		if (mCurFrameTime > 1)
		{
			mCurFrame++;

			if (mCurFrame > mFrameCount)
			{
				mCurFrame = 1;
			}
			mCurFrameTime = 0;
		}
	}
	else
	{
		mCurFrame = 1;
		mCurFrameTime = 0;
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::Jump()
{
	if (!mJumping && mCanJump)
	{
		soundmanager::SoundManager::getInstance()->playFX("SFX/JumpSound.wav");

		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::AddGravity(float deltaTime)
{
    mPosition.y += GravityValue * deltaTime;
    mCanJump = false;
}

void Character::CancelJump()
{
	mJumpForce = 0.0f;
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
}

void Character::SetAlive(bool alive)
{
	mAlive = alive;
}

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= movementSpeed * deltaTime;
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += movementSpeed * deltaTime;
}
