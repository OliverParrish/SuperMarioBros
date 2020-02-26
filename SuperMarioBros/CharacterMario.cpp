#include "CharacterMario.h"
#include "Character.h"
#include "Texture2D.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, LevelMap* LevelMap, Vector2D startPosition) : Character(renderer, imagePath, startPosition, LevelMap)
{
	mRenderer = renderer;

	mSingleSpriteWidth = mTexture->GetWidth()/6;
	mSingleSpriteHeight = mTexture->GetHeight();

	mJumpFrame = 6;
	mFrameCount = 4;
}

CharacterMario::~CharacterMario()
{
	delete mRenderer;
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void CharacterMario::Render()
{
	Character::Render();
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	//Handle Events
	switch (e.type)
	{

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = true;
			break;
		case SDLK_RIGHT:
			mMovingRight = true;
			break;
		case SDLK_UP:
			Jump();
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		}
		break;
	}
}
