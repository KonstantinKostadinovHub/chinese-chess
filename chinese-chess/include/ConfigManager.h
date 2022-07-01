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

	static SDL_Texture* m_pawn1;
	static SDL_Texture* m_pawn2;

	static Card* m_card;

	vector<Card*> m_allCards;
};
