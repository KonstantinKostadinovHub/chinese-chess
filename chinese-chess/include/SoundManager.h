#pragma once

#include <SDL_mixer.h>
#include <fstream>

#include "defines.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	
	void init();
	void playSound(SOUND sound);
	void destroy();
	
private:
	Mix_Chunk* m_backgroundMusic;
};