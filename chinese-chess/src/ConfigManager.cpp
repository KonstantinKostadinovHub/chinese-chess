#include "ConfigManager.h"
#include "World.h"

SDL_Texture* ConfigManager::m_pawn1 = nullptr;
SDL_Texture* ConfigManager::m_pawn2 = nullptr;
Card* ConfigManager::m_card = nullptr;

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{

}

void ConfigManager::load()
{
	loadPawn();
	loadCard();
}

void ConfigManager::loadPawn()
{
	m_pawn1 = loadTexture(PAWNS_FOLDER + "pawn1.bmp");
	m_pawn2 = loadTexture(PAWNS_FOLDER + "pawn2.bmp");
}

void ConfigManager::loadCard()
{
	fstream stream;

	string tmp;

	stream.open(CONFIG_FOLDER + CARDS_FOLDER + "allCards.txt");

	while (!stream.eof())
	{
		string name;
		stream >> name;

		m_card->data.texture = loadTexture(GAME_FOLDER + CARDS_FOLDER + name + ".bmp");
		m_card->data.reversedTexture = loadTexture(GAME_FOLDER + CARDS_FOLDER + name + "_reversed.bmp");

		string buff;
		stream >> buff;

		while (buff != ";")
		{
			int2 move;

			move.x = stoi(buff);
			stream >> move.y;
			m_card->data.m_availableMoves.push_back(move);
			stream >> buff;
		}

		m_allCards.push_back(m_card);
	}

	stream.close();
}
