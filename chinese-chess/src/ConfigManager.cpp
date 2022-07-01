#include "ConfigManager.h"
#include "World.h"

SDL_Texture* ConfigManager::m_pawn1 = nullptr;
SDL_Texture* ConfigManager::m_pawn2 = nullptr;

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{

}

void ConfigManager::load()
{
	loadPawn();
}

void ConfigManager::loadPawn()
{
	m_pawn1 = loadTexture(PAWNS_FOLDER + "pawn1.bmp");
	m_pawn2 = loadTexture(PAWNS_FOLDER + "pawn2.bmp");
}