#pragma once
#include "GameScreen.h"
#include "Texture2D.h"

class GameOverScreen: GameScreen
{
public:
	GameOverScreen(SDL_Renderer* renderer);
	~GameOverScreen();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:

	Texture2D* mBackgroundTexture;
};

