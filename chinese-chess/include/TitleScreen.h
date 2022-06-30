#pragma once

#include <fstream>

#include "defines.h"
#include "Engine.h"
#include "State.h"

class TitleScreen : public State
{
public :
	TitleScreen();
	~TitleScreen();

	void init();
	void run();
	void destroy();

private:
	Drawable m_titleScreenLogo;
	DrawableWithOpacity m_titleScreenText;

	void changeOpacity();
};