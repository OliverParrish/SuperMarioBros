#include "GameScreenIntro.h"
#include <iostream>



GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/IntroScreen.png"))
	{
		std::cout << "failed to load background texture!" << std::endl;
	}
}

GameScreenIntro::~GameScreenIntro()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenIntro::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}
	

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
	
}
