#pragma once

#include <fstream>

#include "defines.h"
#include "State.h"
#include "PopUp.h"
#include "Button.h"

class Menu : public State
{
public:
	Menu();
	~Menu();

	void init();
	void run();
	void destroy();
	
private: 
	
	SDL_Texture* m_menuTexture;

	Button m_exitBtn;
	Button m_onePlayerBtn;
	Button m_twoPlayersBtn;

	PopUp* m_popUp;
};