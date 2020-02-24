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
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	};
}

void Character::Update(float deltaTime, SDL_Event e)
{
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + (mTexture->GetHeight())) / TILE_HEIGHT;

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
	if (mPosition.y < (SCREEN_HEIGHT - mTexture->GetHeight())) mPosition.y += GravityValue * deltaTime;
	//allows character to jump
	else if (mPosition.y > (SCREEN_HEIGHT - mTexture->GetHeight()) && !mJumping) mCanJump = true;
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
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
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
