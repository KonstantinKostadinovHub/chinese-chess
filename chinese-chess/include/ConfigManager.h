#pragma once

#include "defines.h"

#include "Presenter.h"

class ConfigManager
{

public:
	ConfigManager();
	~ConfigManager();

	void load();
	void loadPawn();
	void loadCard();
	
	static SDL_Texture* m_senseiPawn1;
	static SDL_Texture* m_senseiPawn2;
	static SDL_Texture* m_pawn1;
	static SDL_Texture* m_pawn2;

	vector<CardData> m_allCards;
};
