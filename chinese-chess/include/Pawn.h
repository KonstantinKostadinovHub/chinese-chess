#pragma once

#include <fstream>

#include "defines.h"

class Pawn : public Drawable
{
public:
	Pawn();
	~Pawn();

	int m_owner; //1 - pl1, 2 - pl2

	int2 m_coor;
};