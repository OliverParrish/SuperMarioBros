#pragma once
#include "GameScreen.h"
#include "Texture2D.h"

class GameScreenWin : GameScreen
{
public:
	GameScreenWin(SDL_Renderer* renderer);
	~GameScreenWin();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:

	Texture2D* mBackgroundTexture;
};
