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

	string tmp, background, buttonClick, placePawn, captureTemple, selectPawn;

	stream.open(SOUND_FOLDER + "music.txt");

	stream >> tmp >> background;
	stream >> tmp >> buttonClick;
	stream >> tmp >> placePawn;
	stream >> tmp >> captureTemple;
	stream >> tmp >> selectPawn;
	
	stream.close();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}

	m_backgroundMusic = Mix_LoadWAV((SOUND_FOLDER + background).c_str());
	m_buttonClick = Mix_LoadWAV((SOUND_FOLDER + buttonClick).c_str());
	m_placePawn = Mix_LoadWAV((SOUND_FOLDER + placePawn).c_str());
	m_captureTemple = Mix_LoadWAV((SOUND_FOLDER + captureTemple).c_str());
	m_selectPawn = Mix_LoadWAV((SOUND_FOLDER + selectPawn).c_str());

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
	case SOUND::BUTTON_CLICK:
		Mix_PlayChannel(2, m_buttonClick, 0);
		Mix_Volume(2, 10);
		break;
	case SOUND::PLACE_PAWN:
		Mix_PlayChannel(3, m_placePawn, 0);
		Mix_Volume(3, 10);
		break;
	case SOUND::CAPTURE_TEMPLE:
		Mix_PlayChannel(4, m_captureTemple, 0);
		Mix_Volume(4, 10);
		break;
	case SOUND::SELECT_PAWN:
		Mix_PlayChannel(5, m_selectPawn, 0);
		Mix_Volume(5, 10);
		break;
	default:
		break;
	}
}

void SoundManager::destroy()
{
	Mix_FreeChunk(m_backgroundMusic);
	m_backgroundMusic = NULL;

	Mix_FreeChunk(m_buttonClick);
	m_buttonClick = NULL;

	Mix_FreeChunk(m_placePawn);
	m_placePawn = NULL;

	Mix_FreeChunk(m_captureTemple);
	m_captureTemple = NULL;

	Mix_FreeChunk(m_selectPawn);
	m_selectPawn = NULL;
}