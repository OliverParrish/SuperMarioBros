#include "GameOverScreen.h"
#include "FontUI.h"
#include "GameManager.h"
#include <iostream>
#include "SoundManager.h"

GameOverScreen::GameOverScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/GameOverScreen.png"))
	{
		std::cout << "failed to load background texture!" << std::endl;
	}

	soundmanager::SoundManager::getInstance()->stopMusic();
	soundmanager::SoundManager::getInstance()->playFX("Music/GameOver.wav");


}

GameOverScreen::~GameOverScreen()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameOverScreen::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	GameManager::getInstance()->mScoreText->SetPosition(new Vector2D(325 - 50, 150));
	GameManager::getInstance()->mScoreText->Draw();
}

void GameOverScreen::Update(float deltaTime, SDL_Event e)
{
}
