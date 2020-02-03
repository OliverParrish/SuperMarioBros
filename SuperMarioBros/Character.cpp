#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Collisions.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);

	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "could not load character Image file" << std::endl;
	}
	mPosition = startPosition;

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
	//Apply Gravity
	AddGravity(deltaTime);
	
	//Jumping for Mario
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

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
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
