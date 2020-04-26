#include "GameManager.h"

GameManager* GameManager::instance = 0;

void GameManager::AddScore(int add)
{
	score += add;

	if (mScoreText != nullptr)
	{
		std::string scoreString = "Score: " + std::to_string(score);
		const char* score = scoreString.c_str();
		mScoreText->SetText(score);

		mScoreText->UpdateSurface();
		mScoreText->UpdateTexture();
	}
}

void GameManager::SetScore(int score)
{
	this->score = score;

	if (mScoreText != nullptr)
	{
		std::string scoreString = "Score: " + std::to_string(score);
		const char* score = scoreString.c_str();
		mScoreText->SetText(score);

		mScoreText->UpdateSurface();
		mScoreText->UpdateTexture();
	}
}
