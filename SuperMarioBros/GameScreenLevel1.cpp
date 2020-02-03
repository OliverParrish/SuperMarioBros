#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete myCharacter;
	myCharacter = NULL;
}
void GameScreenLevel1::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	//Draw the Player
	myCharacter->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	myCharacter->Update(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "failed to load background texture!";
		return false;
	}
	myCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));
	return true;
}
