#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Collisions.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	//Renderer for the texture of characters
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);

	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "could not load character Image file" << std::endl;
	}
	//Start position Renderer
	mPosition = startPosition;

	mCurrentLevelMap = map;

	mFacingDirection = FACING_RIGHT;

	mMovingLeft = false;
	mMovingRight = false;
	mJumping = false;
	mFrameCount = 1;

	mCollisionRadius = 15.0f;
}

Character::~Character()
{
	delete mRenderer;
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void Character::Render()
{
	//get position of sprite sheet
	int left = mSingleSpriteWidth * (mFrameCount - 1);
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	//character animation
	UpdateFrame(deltaTime);

	int centralXPosition = (int)(mPosition.x + (mSingleSpriteWidth * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + (mSingleSpriteHeight)) / TILE_HEIGHT;

	//Apply Gravity
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		mCanJump = true;
	}
	
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
	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	
}

void Character::UpdateFrame(float deltaTime)
{
	if (IsJumping() || !mCanJump)
	{
		mFrameCount = 6;
	}
	else if (mMovingRight || mMovingLeft)
	{
		mCurFrameTime += deltaTime * 10;

		if (mCurFrameTime > 1)
		{
			mFrameCount++;

			if (mFrameCount > 4)
			{
				mFrameCount = 1;
			}
			mCurFrameTime = 0;
		}
	}
	else
	{
		mFrameCount = 1;
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

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= MovementSpeed * deltaTime;
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += MovementSpeed * deltaTime;
}
