#include "SDL.h"
#include "Character.h"
#include "Texture2D.h"
#include "CharacterKoopa.h"




CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, TileMap* LevelMap, Vector2D startPosition, float speed, FACING direction) : Character(renderer, imagePath, startPosition, LevelMap)
{
	mInjured = false;
	movementSpeed = speed;
	mFacingDirection = direction;
	mSingleSpriteHeight = mTexture->GetHeight();
	mSingleSpriteWidth = mTexture->GetWidth() / 6;
	mAlive = true;

	mJumpFrame = 5;
	mFrameCount = 4;
}

CharacterKoopa::~CharacterKoopa()
{
	delete mRenderer;
	mRenderer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = 2.5f;

	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	if (!mAlive) return;
	if (!mInjured)
	{
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else
	{
		mMovingLeft = false;
		mMovingRight = false;

		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0.0)
		{
			Flip();
		}
	}

	//character update function
	Character::Update(deltaTime, e);
}

void CharacterKoopa::Render(int x, int y)
{
	int left = mSingleSpriteWidth * (mCurFrame - 1);

	if (IsInjured())
	{
		left = mSingleSpriteWidth * mJumpFrame;
	}

	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(Vector2D(mPosition.x - x, mPosition.y - y), &portionOfSpriteSheet, 0.0, nullptr, SDL_FLIP_NONE);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(Vector2D(mPosition.x - x, mPosition.y - y), &portionOfSpriteSheet, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Flip()
{
	if (mFacingDirection == FACING_RIGHT)
		mFacingDirection = FACING_LEFT;
	else if (mFacingDirection == FACING_LEFT)
		mFacingDirection = FACING_RIGHT;

	mInjured = false;
	Jump();
		
}

