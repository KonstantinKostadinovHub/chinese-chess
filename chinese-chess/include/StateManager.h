#pragma once

#include "Game.h"
#include "TitleScreen.h"
#include "Menu.h"
#include "WinScreen.h"

enum class GAME_STATE
{
	NONE = 0,
	GAME = 1,
	TITLE_SCREEN = 2,
	MENU = 3,
	WIN_SCREEN = 4
};

/*
* \brief managing game states
* After switching to the next game state, delete the
* old one and all the create a new one. Loading screens
* must be playd between the creation and destruction of
* objects
*/
class StateManager
{
public:
	StateManager();
	~StateManager();

	GAME_STATE m_gameState;

	Game* m_game;
	TitleScreen* m_titleScreen;
	Menu* m_menu;
	WinScreen* m_winScreen;
	
	State* m_currState;
	
	void init(GAME_STATE _state);
	void run();

	void changeGameState(GAME_STATE _state);

private:
	void initNewState();
	void destroyLastState();
};