#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "LevelMap.h"
#include <vector>

class Character;
class Texture2D;
class PowBlock;

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
	void SetLevelMap();
	void DoScreenShake();

	bool mScreenshake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;

	PowBlock* mPowBlock;
	void UpdatePowBlock();

	CharacterMario* mario;
	CharacterLuigi* luigi;
	LevelMap* mLevelMap;

	std::vector<CharacterKoopa*> mEnemies;
	int enemyIndexToDelete;

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D pos, FACING direction, float speed);

};
