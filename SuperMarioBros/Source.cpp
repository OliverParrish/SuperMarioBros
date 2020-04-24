#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "SoundManager.h"
#include <iostream>
#include "GameScreenManager.h"
#include <filesystem>
#include <SDL_ttf.h>
#include "Camera.h"
#include "GameManager.h"

using namespace std;

// Global Variables
SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
Mix_Music* gMusic = NULL;

Uint32 gOldTime;

bool InitSDL();
bool Update();
void CloseSDL();
void Render();
void LoadMusic(std::string source);


int main(int argc, char* args[])
{
	bool quit = false;
	if (InitSDL())
	{
		gOldTime = SDL_GetTicks();

		//set up game screen manager
		GameManager::getInstance()->mGameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);

		// initialise camera
		Camera::GetInstance();

		while (!quit)
		{
			Render();
			quit = Update();
		}

	}

	CloseSDL();

	return 0;

}

bool InitSDL()
{

	

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{

		gWindow = SDL_CreateWindow("Games Engine Creation", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

	}
	if (gWindow == NULL)
	{
		cout << "Window was not created. Error: " << SDL_GetError();
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	if (gRenderer != NULL)
	{
		//load background texture.
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags)& imageFlags))
		{
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}

		// Initialise mixer
		soundmanager::SoundManager::getInstance();

		Mix_Volume(-1, SDL_MIX_MAXVOLUME / 4);
		Mix_VolumeMusic(SDL_MIX_MAXVOLUME / 6);

		TTF_Init();
	}
	else
	{
		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}

	

	return true;

	
}
void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	IMG_Quit();
	SDL_Quit();

}

void Render()
{
	//clear the screen - black
	SDL_SetRenderDrawColor(gRenderer, 100, 160, 255, 0x00);
	SDL_RenderClear(gRenderer);

	if (GameManager::getInstance()->mGameScreenManager->mCurrentScreen != nullptr)
	{
		GameManager::getInstance()->mGameScreenManager->mCurrentScreen->Render();

	}

	//update screen
	SDL_RenderPresent(gRenderer);
}

bool Update()
{
	Uint32 newTime = SDL_GetTicks();
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_QUIT:
		return true;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			return true;
		}
		break;
		
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			GameManager::getInstance()->mGameScreenManager->ChangeScreen(SCREEN_LEVEL1);
		}
		break;
	}
	if (GameManager::getInstance()->mGameScreenManager->mCurrentScreen != nullptr)
	{
		GameManager::getInstance()->mGameScreenManager->mCurrentScreen->Update((float)(newTime - gOldTime) / 1000.0f, e); 

	}
	gOldTime = newTime;
	return false;
}
