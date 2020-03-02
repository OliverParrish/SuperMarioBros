#pragma once

#ifndef _SOUNDMANGER_H
#define _SOUNDMANGER_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <string>
#include <iostream>

namespace soundmanager
{
	class SoundManager
	{
	public:

		static SoundManager* getInstance()
		{
			if (instance == 0)
			{
				instance = new SoundManager;
				SoundManager::initAudioDevice();
			}
			return instance;
		}

		void playMusic(const std::string& fileName);
		void stopMusic();
		void playFX(const std::string& fileName) const;

		inline bool isStopped() const
		{
			return currentState == STOPPED;
		}

		inline bool isPlaying() const 
		{
			return currentState == PLAYING;
		}

		inline bool isErrorState() const
		{
			return currentState == ERROR;
		}


	private:

		static SoundManager* instance;

		enum AudioState
		{
			ERROR = 0,
			WAITING,
			STOPPED,
			PLAYING
		};

		static AudioState currentState;

		static void initAudioDevice()
		{
			if (SDL_Init(SDL_INIT_AUDIO) != -1)
			{
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					std::cout << "Mixer could not initialise. Error: " << Mix_GetError();
					currentState = ERROR;
				}
				else
				{
					currentState = WAITING;
				}
			}
			else
			{
				std::cerr << "Error initializing SDL audio ";
				currentState = ERROR;
			}
		}

		SoundManager()
		{
		}

		SoundManager(const SoundManager&)
		{
		}

		SoundManager& operator=(const SoundManager&)
		{
		}

		~SoundManager()
		{
			Mix_CloseAudio();
		}
	};

}

#endif