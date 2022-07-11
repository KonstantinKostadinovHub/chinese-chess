#pragma once

#include <fstream>

#include "defines.h"
#include "Button.h"

class PopUp
{
public:
	PopUp();
	~PopUp();

	void init();
	void run();
	void destroy();

	Button* m_easyBtn;
	Button* m_hardBtn;

private:
	Drawable m_difficulty;
};