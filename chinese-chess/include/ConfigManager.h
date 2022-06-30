#pragma once

#include "defines.h"

#include "Pawn.h"
#include "Presenter.h"

class ConfigManager
{

public:
	ConfigManager();
	~ConfigManager();

	void load();
	void loadPawn();

	static SDL_Texture* m_pawn1;
	static SDL_Texture* m_pawn2;
	//static Entity* m_enityModelPlayer2;
	//static Entity* m_enityModelEnemy;
	//static Entity* m_enityModel;
};
