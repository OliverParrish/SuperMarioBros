#pragma once
#include "GameScreenManager.h"
#include "FontUI.h"
class GameManager
{
public:

	static GameManager* getInstance()
	{
		if (instance == 0)
		{
			instance = new GameManager;
			instance->initalise();
		}
		return instance;
	}

	GameScreenManager* mGameScreenManager;

	void AddScore(int add);
	void SetScore(int score);
	int GetScore() { return score; }
	FontUI* mScoreText;


private:

	int score;

	static GameManager* instance;

	void initalise()
	{
		score = 0;
	}
};