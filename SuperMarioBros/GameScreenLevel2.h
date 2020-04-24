#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "LevelMap.h"
#include "Coin.h"
#include "FontUI.h"
#include "TileMap.h"
#include <vector>

class Character;
class Texture2D;
class PowBlock;

class GameScreenLevel2 : GameScreen
{

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);


private:

	Texture2D* mBackgroundTexture;

	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();
	bool FlagCollision();

	bool mScreenshake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;

	PowBlock* mPowBlock;
	void UpdatePowBlock();

	CharacterMario* mCharacterMario;
	CharacterLuigi* mCharacterLuigi;
	LevelMap* mLevelMap;
	TileMap* mTileMap;

	std::vector<CharacterKoopa*> mEnemies;
	int enemyIndexToDelete;

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D pos, FACING direction, float speed);

	std::vector<Coin*> mCoins;
	int coinIndexToDelete;

	void UpdateCoins(float deltaTime);
	void CreateCoin(Vector2D pos);
};
