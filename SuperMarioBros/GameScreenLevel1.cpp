#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;
}
void GameScreenLevel1::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	//Draw the Player
	mario->Render();
	luigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(mario, luigi))
	{
		std::cout << "woiqjeuwqiewq" << std::endl;
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "failed to load background texture!";
		return false;
	}
	mario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330));
	luigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(364, 330));
	return true;
}
