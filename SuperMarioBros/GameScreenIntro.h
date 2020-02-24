#pragma once

#include "GameScreen.h"
#include "Texture2D.h"



class GameScreenIntro : GameScreen
{
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:

	Texture2D* mBackgroundTexture;

};
