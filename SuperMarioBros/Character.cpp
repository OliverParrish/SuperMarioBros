#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);

	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "could not load character Image file" << std::endl;
	}
	mPosition = startPosition;
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	mTexture->Render(mPosition, SDL_FLIP_NONE);
}

void Character::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mPosition.x -= 1;
			break;
		case SDLK_RIGHT:
			mPosition.x += 1;
			break;
		}
		break;
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return Vector2D();
}
