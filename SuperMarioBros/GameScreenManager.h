#pragma once
#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"

class GameScreenManager
{
public:

	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);

	GameScreen* mCurrentScreen;

private:

	SDL_Renderer* mRenderer;

};