#pragma once

#include <fstream>

#include "defines.h"
#include "State.h"
#include "Button.h"

class WinScreen : public State
{
public:
	WinScreen();
	~WinScreen();

	void init();
	void run();
	void destroy();
	
private:
	Drawable m_winScreenPl1;
	Drawable m_winScreenPl2;
	Drawable m_defeat;
	
	SDL_Texture* m_background;
	
	Button m_playBtn;
	Button m_exitBtn;
};