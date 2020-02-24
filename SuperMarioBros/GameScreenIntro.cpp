#include "GameScreenIntro.h"
#include "Source.cpp"



GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{

}

GameScreenIntro::~GameScreenIntro()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenIntro::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);

	if (!mBackgroundTexture->LoadFromFile("Images/IntroScreen.png"))
	{
		std::cout << "failed to load background texture!" << std::endl;
	}
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
	
}
