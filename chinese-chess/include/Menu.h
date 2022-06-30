#pragma once

#include <fstream>

#include "defines.h"
#include "State.h"
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

	bool m_isValid;
	
	Drawable m_menu;
};