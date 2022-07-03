#include "ConfigManager.h"
#include "World.h"

SDL_Texture* ConfigManager::m_senseiPawn1 = nullptr;
SDL_Texture* ConfigManager::m_pawn1 = nullptr;
SDL_Texture* ConfigManager::m_senseiPawn2 = nullptr;
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
	loadCard();
}

void ConfigManager::loadPawn()
{
	m_senseiPawn1 = loadTexture(PAWNS_FOLDER + "senseiPawn1.bmp");
	m_pawn1 = loadTexture(PAWNS_FOLDER + "pawn1.bmp");
	m_senseiPawn2 = loadTexture(PAWNS_FOLDER + "senseiPawn2.bmp");
	m_pawn2 = loadTexture(PAWNS_FOLDER + "pawn2.bmp");
}

void ConfigManager::loadCard()
{
	fstream stream;

	string tmp;

	stream.open(CONFIG_FOLDER + CARDS_FOLDER + "allCards.txt");

	while (!stream.eof())
	{
		CardData _card;

		string name;
		stream >> name;

		_card.texture = loadTexture(GAME_FOLDER + CARDS_FOLDER + name + ".bmp");
		_card.reversedTexture = loadTexture(GAME_FOLDER + CARDS_FOLDER + name + "_reversed.bmp");

		string buff;
		stream >> buff;

		while (buff != ";")
		{
			int2 move;

			move.x = stoi(buff);
			stream >> move.y;
			_card.m_availableMoves.push_back(move);
			stream >> buff;
		}

		m_allCards.push_back(_card);
	}

	stream.close();
}
