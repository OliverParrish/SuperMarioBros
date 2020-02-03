#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"

class Character;
class Texture2D;

class GameScreenLevel1 : GameScreen
{

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	
	void Render();
	void Update(float deltaTime, SDL_Event e);

private:

	Texture2D* mBackgroundTexture;

	bool SetUpLevel();

	CharacterMario* mario;
	CharacterLuigi* luigi;
};
