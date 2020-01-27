#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include <iostream>
#include "GameScreenManager.h"

using namespace std;

// Global Variables
SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;

GameScreenManager* gameScreenManager;

Uint32 gOldTime;

bool InitSDL();
bool Update();
void CloseSDL();
void Render();


int main(int argc, char* args[])
{
	bool quit = false;
	if (InitSDL())
	{
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		gOldTime = SDL_GetTicks();

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
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags)& imageFlags))
		{
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}

		//load background texture.

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
	}
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return false;
}