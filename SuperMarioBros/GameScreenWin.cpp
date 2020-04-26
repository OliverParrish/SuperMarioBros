#include "GameScreenWin.h"
#include "FontUI.h"
#include "GameManager.h"
#include <iostream>
#include "SoundManager.h"

GameScreenWin::GameScreenWin(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/GameWinScreen.png"))
	{
		std::cout << "failed to load background texture!" << std::endl;
	}

	soundmanager::SoundManager::getInstance()->stopMusic();
	soundmanager::SoundManager::getInstance()->playFX("Music/GameWin.wav");

}

GameScreenWin::~GameScreenWin()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenWin::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	GameManager::getInstance()->mScoreText->SetPosition(new Vector2D(325 - 50, 50));
	GameManager::getInstance()->mScoreText->Draw();
}

void GameScreenWin::Update(float deltaTime, SDL_Event e)
{
}
