#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include <iostream>
#include "GameScreenManager.h"
#include <filesystem>

using namespace std;

// Global Variables
SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
Mix_Music* gMusic = NULL;

GameScreenManager* gameScreenManager;

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
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);
		gOldTime = SDL_GetTicks();

		LoadMusic("Music/Mario.wav");
		if (Mix_PlayingMusic()==0)
		{
			Mix_PlayMusic(gMusic, -1);
		}

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
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not initialise. Error: " << Mix_GetError();
		}
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

	delete gameScreenManager;
	gameScreenManager = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	IMG_Quit();
	SDL_Quit();

}

void Render()
{
	//clear the screen - black
	SDL_SetRenderDrawColor(gRenderer, 0x01, 0x01, 0x01, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	//update screen
	SDL_RenderPresent(gRenderer);
}

void LoadMusic(std::string source)
{
	gMusic = Mix_LoadMUS(source.c_str());

	if (gMusic == NULL)
	{
		cout << "failed to load the background music. Error: " << Mix_GetError() << endl;
	}

	
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
			gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		}
		break;
	}
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return false;
}
