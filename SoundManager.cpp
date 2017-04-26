//
//  Sound.cpp
//  hockeygame
//
//  Created by Peter Ju on 3/29/15.
//  Copyright (c) 2015 Peter Ju. All rights reserved.
//

#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance;

SoundManager::SoundManager()
{

	//sound frequency, format, channels, sample size
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}


bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
		if (pMusic == 0)
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}

		m_music[id] = pMusic;
		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
		if (pChunk == 0)
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}

		m_sfxs[id] = pChunk;
		return true;
	}
	//else if(type == )
	return false;
}

void SoundManager::playMusic(std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(std::string id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}

