#include "SoundManager.h"
#include "SDL_mixer.h"
#include <string>

using namespace soundmanager;

SoundManager* SoundManager::instance = 0;
SoundManager::AudioState SoundManager::currentState = ERROR;


void soundmanager::SoundManager::playMusic(const std::string& fileName)
{
	if (currentState != ERROR)
	{
		// if no music is playing, play the music
		if (Mix_PlayingMusic() == 0)
		{
			Mix_Music* music = Mix_LoadMUS(fileName.c_str());

			if (music == NULL)
			{
				//display error but remain in the same state 
				//since nothing has changed
				std::cerr << "Error loading music file: " << fileName << std::endl;
			}
			else
			{
				//play music
				Mix_PlayMusic(music, -1);
				currentState = PLAYING;
			}
		}
		else
		{
			//if music is already playing, then pause it
			this->stopMusic();
		}
	}
}

void soundmanager::SoundManager::stopMusic()
{
	if (currentState != ERROR)
	{
		Mix_HaltMusic();
		currentState = STOPPED;
	}
}

void soundmanager::SoundManager::playFX(const std::string& fileName) const
{
	if (currentState != ERROR)
	{
		Mix_Chunk* fx = Mix_LoadWAV(fileName.c_str());

		if (fx == NULL)
		{
			std::cerr << "Error loading music file: " << fileName << std::endl;
		}
		else
		{
			Mix_PlayChannel(-1, fx, 0);
		}
	}
}
