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

/*
void ConfigManager::loadEntity()
{
	m_enityModelPlayer1 = new Entity();
	m_enityModelPlayer1->load("player1");
	m_enityModelPlayer2 = new Entity();
	m_enityModelPlayer2->load("player2");
	m_enityModelEnemy = new Entity();
	m_enityModelEnemy->load("ai");
}
*/