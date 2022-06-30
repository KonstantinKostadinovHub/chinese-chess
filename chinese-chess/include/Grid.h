#pragma once

#include "Presenter.h"
#include "Validator.h"
#include <map>

constexpr int BOARD_SIZE = 5;


/*
\brief Grid structure splitting a place into gridded squares
*/

class Grid
{

public:
	Grid();
	~Grid();

	int m_winner = 0;		// shows the winner of the game

	Drawable m_gridSquares[BOARD_SIZE][BOARD_SIZE];

	void load();

	void update();
	void draw();

	void winCondition();
	
	void destroy();
private:
	SDL_Texture* m_background;

	Drawable m_player1OnTurn;
	Drawable m_player2OnTurn;
	Drawable m_tutorial;
	
	Drawable m_availableMove;	// possible to move square
	Drawable m_hover;		// the drawable for hovering

	Drawable* m_hoverGrid;// the grid that we hover on

	/*
	vector<Entity*> m_entities;
	Entity* m_currentEntity = nullptr;
	int2 m_lastEntityCoordinates;
	*/

	vector<Drawable*> m_availableMoves;

	int m_onTurn; // 0 - none, pos number - player

	void checkForClick();
	void onHover();

	void drawHover();
	void drawGridSquares();
	void drawEntities();
	void drawAvailableMoves();
	void calcAvailableMoves();

	bool possMove(int2 coor);

	bool m_drawTutorial = false;
};