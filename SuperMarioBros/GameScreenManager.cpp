#include "GameScreenManager.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenIntro.h"
#include "GameOverScreen.h"
#include "GameScreenWin.h"



GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;

}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen;
	GameScreenLevel2* level2Temp;
	GameOverScreen* gameOverTemp;
	GameScreenIntro* introScreen;
	GameScreenWin* winTemp;
	
	switch (newScreen)
	{
	case SCREEN_INTRO:
		introScreen = new GameScreenIntro(mRenderer);
		mCurrentScreen = (GameScreen*)introScreen;
		introScreen = NULL;
		break;
	case SCRREN_MENU:
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_LEVEL2:
		level2Temp = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)level2Temp;
		level2Temp = NULL;
		break;
	case SCREEN_GAMEOVER:
		gameOverTemp = new GameOverScreen(mRenderer);
		mCurrentScreen = (GameScreen*)gameOverTemp;
		gameOverTemp = NULL;
		break;
	case SCREEN_WIN:
		winTemp = new GameScreenWin(mRenderer);
		mCurrentScreen = (GameScreen*)winTemp;
		winTemp = NULL;
		break;
	default:
		break;
	}
}
