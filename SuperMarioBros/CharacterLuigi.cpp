#include "CharacterLuigi.h"
#include "Character.h"
#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, LevelMap* LevelMap, Vector2D startPosition) : Character(renderer, imagePath, startPosition, LevelMap)
{
	mRenderer = renderer;

	mSingleSpriteWidth = mTexture->GetWidth() / 6;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterLuigi::~CharacterLuigi()
{
	delete mRenderer;
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void CharacterLuigi::Render()
{
	Character::Render();
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	//Handle Events
	switch (e.type)
	{

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = true;
			break;
		case SDLK_d:
			mMovingRight = true;
			break;
		case SDLK_w:
			Jump();
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		}
		break;
	}
}
