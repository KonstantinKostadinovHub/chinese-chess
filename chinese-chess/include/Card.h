#pragma once

#include <fstream>

#include "defines.h"

class Card : Drawable
{
public:
	Card();
	~Card();

	void init(string configFile);
	void destroy();

	int m_onTurn; // 1 - pl1, 2 - pl2, -1 - pl1 will get the card, -2 - pl2 will get the card

	vector<int2> m_moves;
};