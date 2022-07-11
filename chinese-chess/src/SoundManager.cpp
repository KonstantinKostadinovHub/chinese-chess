#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	
}

void SoundManager::init()
{
	fstream stream;

	string tmp, background;

	stream.open(SOUND_FOLDER + "music.txt");

	stream >> tmp >> background;
	
	stream.close();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}

	m_backgroundMusic = Mix_LoadWAV((SOUND_FOLDER + background).c_str());

	playSound(SOUND::BACKGROUND);
}

void SoundManager::playSound(SOUND sound)
{
	Mix_AllocateChannels(5);

	switch (sound)
	{
	case SOUND::BACKGROUND:
		Mix_PlayChannel(1, m_backgroundMusic, -1);
		Mix_Volume(1, 10);
		break;
	default:
		break;
	}
}

void SoundManager::destroy()
{
	Mix_FreeChunk(m_backgroundMusic);
	m_backgroundMusic = NULL;
}