#include "Flag.h"
#include <iostream>

Flag::Flag(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, SCREENS* changeScreen)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);

	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cerr << "Could not load coin image from " << imagePath << std::endl;
	}
	mPosition = startPosition;
	mChangeScreen = changeScreen;

	mBoxCollision = Rect2D(mPosition.x, mPosition.y, mTexture->GetHeight(), mTexture->GetWidth());

	
}

Flag::~Flag()
{
	delete mRenderer;
	mRenderer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Flag::Render(int camX, int camY)
{
	mTexture->Render(Vector2D(mPosition.x - camX, mPosition.y - camY), nullptr, 0.0, nullptr, SDL_FLIP_NONE);
}


void Flag::Update(float deltaTime)
{

}
