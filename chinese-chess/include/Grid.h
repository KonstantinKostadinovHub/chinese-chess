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

	int winner = 0;
	int m_gameType; // 0 - 2 players   1 - easy bot   2 - hard bot

	Drawable m_gridSquares[BOARD_SIZE][BOARD_SIZE];

	void load();

	void update();
	void draw();
	
	void destroy();

	int checkForWinner(); //returns the winner of the game

private:
	SDL_Texture* m_background;

	Drawable m_player1OnTurn;
	Drawable m_player2OnTurn;
	
	Drawable m_availableMove;	// possible to move square
	Drawable m_hover;		// the drawable for hovering

	Drawable* m_hoverGrid;// the grid that we hover on
	Drawable m_drawSelectedPawn;
	Drawable m_drawSelectedCard;

	Card* m_selectedCard;
	Pawn* m_selectedPawn;

	vector<Pawn> m_player1Pawns;
	vector<Pawn> m_player2Pawns;

	Card* m_player1Cards[2];
	Card* m_player2Cards[2];
	Card* m_player1nextMove;
	Card* m_player2nextMove;

	vector<Drawable*> m_availableMoves;

	int m_onTurn; // 0 - none, pos number - player

	bool m_selected;

	vector<int2> availableMoves(Pawn* pawn, Card* card);

	void loadPawns();

	void select();
	void selectPawns();
	void selectCards();
	void killPawn(int2 coor);

	void checkForClick();
	void onHover();

	void drawHover();
	void drawGridSquares();
	void drawPawns();
	void drawCards();
	void drawAvailableMoves();
	void calcAvailableMoves();

	void cardSwitch();

	bool possMove(int2 coor);

	vector<int> getRandomIndexes(int start, int finish, int amount);
	void flipCard(Card* card);

	void easyBot();
	void hardBot();
};