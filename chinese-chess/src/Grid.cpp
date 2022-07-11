#include "Grid.h"

#include <assert.h> /* assert */
#include <set> /* set */

#include "World.h"

extern World world;

Grid::Grid()
{
	m_hoverGrid = nullptr;
	m_onTurn = 1;
}

Grid::~Grid()
{
}

bool wait = false;

void Grid::load() 
{
	int2 coordinates, cardDim; // from where do we start

	string temp , player1OnTurn, player2OnTurn;
	
	fstream stream;

	int squareSize;
	
	m_player1Cards[0] = new Card;
	m_player1Cards[1] = new Card;
	m_player2Cards[0] = new Card;
	m_player2Cards[1] = new Card;
	m_player1nextMove = new Card;
	m_player2nextMove = new Card;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "grid.txt");

	stream >> temp >> squareSize;

	stream >> temp >> m_player1OnTurn.rect.x >> m_player1OnTurn.rect.y >> m_player1OnTurn.rect.w >> m_player1OnTurn.rect.h;
	stream >> temp >> m_player2OnTurn.rect.x >> m_player2OnTurn.rect.y >> m_player2OnTurn.rect.w >> m_player2OnTurn.rect.h;
	stream >> temp >> player1OnTurn >> player2OnTurn;
	
	stream >> temp >> temp;

	m_drawSelectedPawn.texture = loadTexture(GAME_FOLDER + temp);

	stream >> temp >> temp;

	m_drawSelectedCard.texture = loadTexture(GAME_FOLDER + temp);

	stream >> temp >> cardDim.x >> cardDim.y;

	stream >> temp >> temp;
	stream >> temp >> m_player1Cards[0]->rect.x >> m_player1Cards[0]->rect.y;
	m_player1Cards[0]->rect.w = cardDim.x;
	m_player1Cards[0]->rect.h = cardDim.y;

	stream >> temp >> temp;
	stream >> temp >> m_player1Cards[1]->rect.x >> m_player1Cards[1]->rect.y;
	m_player1Cards[1]->rect.w = cardDim.x;
	m_player1Cards[1]->rect.h = cardDim.y;

	stream >> temp >> temp;
	stream >> temp >> m_player2Cards[0]->rect.x >> m_player2Cards[0]->rect.y;
	m_player2Cards[0]->rect.w = cardDim.x;
	m_player2Cards[0]->rect.h = cardDim.y;
	
	stream >> temp >> temp;
	stream >> temp >> m_player2Cards[1]->rect.x >> m_player2Cards[1]->rect.y;
	m_player2Cards[1]->rect.w = cardDim.x;
	m_player2Cards[1]->rect.h = cardDim.y;

	stream >> temp >> temp;
	stream >> temp >> m_player1nextMove->rect.x >> m_player1nextMove->rect.y;
	m_player1nextMove->rect.w = cardDim.x;
	m_player1nextMove->rect.h = cardDim.y;

	stream >> temp >> temp;
	stream >> temp >> m_player2nextMove->rect.x >> m_player2nextMove->rect.y;
	m_player2nextMove->rect.w = cardDim.x;
	m_player2nextMove->rect.h = cardDim.y;

	stream.close();

	// choose random indexes among the cards

	vector<int> randomIndexes = getRandomIndexes(0,world.m_config.m_allCards.size() - 1, 6);

	m_player1Cards[0]->data = world.m_config.m_allCards[randomIndexes[0]];
	m_player1Cards[0]->texture = m_player1Cards[0]->data.texture;

	m_player1Cards[1]->data = world.m_config.m_allCards[randomIndexes[1]];
	m_player1Cards[1]->texture = m_player1Cards[1]->data.texture;

	m_player2Cards[0]->data = world.m_config.m_allCards[randomIndexes[2]];
	flipCard(m_player2Cards[0]);

	m_player2Cards[1]->data = world.m_config.m_allCards[randomIndexes[3]];
	flipCard(m_player2Cards[1]);

	m_player1nextMove->data = world.m_config.m_allCards[randomIndexes[4]];
	flipCard(m_player1nextMove);
	m_player1nextMove->texture = m_player1nextMove->data.texture;

	m_player1OnTurn.texture = loadTexture(GAME_FOLDER + player1OnTurn);
	m_player2OnTurn.texture = loadTexture(GAME_FOLDER + player2OnTurn);

	m_availableMove.texture = loadTexture(GAME_FOLDER + "gridPossMove.bmp");
	m_hover.texture = loadTexture(GAME_FOLDER + "hover.bmp");
	
	m_background = loadTexture(GAME_FOLDER + "background.bmp");

	coordinates.x = (Presenter::m_SCREEN_WIDTH - squareSize * BOARD_SIZE) / 2;
	coordinates.y = (Presenter::m_SCREEN_HEIGHT - squareSize * BOARD_SIZE) / 2;	
		
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			m_gridSquares[r][c].rect = { c * squareSize + coordinates.x,
				r * squareSize + coordinates.y, squareSize, squareSize};
		}
	}

	winner = 0;

	loadPawns();
}

void Grid::draw()
{
	drawObject(m_background);

	drawGridSquares();

	drawAvailableMoves();

	drawPawns();

	drawCards();

	drawHover();
	
	
	if (m_onTurn == 1)
	{
		drawObject(m_player1OnTurn);
	}
	else if(m_onTurn == 2)
	{
		drawObject(m_player2OnTurn);
	}
}

void Grid::destroy()
{
	m_player1Pawns.clear();
	m_player2Pawns.clear();

	SDL_DestroyTexture(m_gridSquares[0][0].texture);
}

vector<int2> Grid::availableMoves(Pawn* pawn, Card* card)
{
	return vector<int2>();
}

void Grid::loadPawns()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		Pawn buff;

		buff.m_coor.x = i;
		buff.m_coor.y = 0;
		buff.rect = m_gridSquares[i][0].rect;
		if (i == 2)
		{
			buff.texture = ConfigManager::m_senseiPawn1;
			buff.isSensei = true;
		}
		else
		{
			buff.texture = ConfigManager::m_pawn1;
			buff.isSensei = false;
		}

		buff.m_owner = 1;
		m_player1Pawns.push_back(buff);

		buff.m_coor.x = i;
		buff.m_coor.y = BOARD_SIZE - 1;
		buff.rect = m_gridSquares[i][BOARD_SIZE - 1].rect;

		if (i == 2)
		{
			buff.texture = ConfigManager::m_senseiPawn2;
			buff.isSensei = true;
		}
		else
		{
			buff.texture = ConfigManager::m_pawn2;
			buff.isSensei = false;
		}
		buff.m_owner = 2;
		m_player2Pawns.push_back(buff);
	}
}

void Grid::select()
{
	if (mouseIsPressed())
	{
		m_selected = false;

		selectPawns();
		selectCards();

		if (!m_selected)
		{
			m_selectedCard = nullptr;
			m_selectedPawn = nullptr;
		}
	}
}

void Grid::selectPawns()
{
	bool selected = false;

	if (m_onTurn == 1)
	{
		for (int i = 0; i < m_player1Pawns.size(); i++)
		{
			if (isMouseInRect(m_player1Pawns[i].rect))
			{
				m_selectedPawn = &m_player1Pawns[i];
				selected = true;
				m_selected = true;
			}
		}
	}
	else if (m_gameType == 0 && m_onTurn == 2)
	{
		for (int i = 0; i < m_player2Pawns.size(); i++)
		{
			if (isMouseInRect(m_player2Pawns[i].rect))
			{
				m_selectedPawn = &m_player2Pawns[i];
				selected = true;
				m_selected = true;
			}
		}
	}

	if (!selected)
	{
		if (m_selectedPawn != nullptr)
		{
			for (int r = 0; r < BOARD_SIZE; r++)
			{
				for (int c = 0; c < BOARD_SIZE; c++)
				{
					if (isMouseInRect(m_gridSquares[r][c].rect))
					{
						if (possMove({ r, c }))
						{
							killPawn({ r, c });
							m_selectedPawn->m_coor.x = r;
							m_selectedPawn->m_coor.y = c;

							m_selectedPawn->rect = m_gridSquares[r][c].rect;

							cardSwitch();

							m_onTurn = (m_onTurn == 1) + 1;

							m_selectedPawn = nullptr;
						}
					}
				}
			}
		}
	}
	else
	{
		m_drawSelectedPawn.rect = m_selectedPawn->rect;
	}
}

void Grid::selectCards()
{
	if (m_onTurn == 1)
	{
		for (int i = 0; i < 2; i++)
		{
			if (isMouseInRect(m_player1Cards[i]->rect))
			{
				m_selectedCard = m_player1Cards[i];
				m_drawSelectedCard.rect = m_selectedCard->rect;
				m_selected = true;
			}
		}
	}
	else if (m_gameType == 0 && m_onTurn == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			if (isMouseInRect(m_player2Cards[i]->rect))
			{
				m_selectedCard = m_player2Cards[i];
				m_drawSelectedCard.rect = m_selectedCard->rect;
				m_selected = true;
			}
		}
	}
}

void Grid::killPawn(int2 coor)
{
	for (int i = 0; i < m_player1Pawns.size(); i++)
	{
		if (m_player1Pawns[i].m_coor == coor)
		{
			m_player1Pawns.erase(m_player1Pawns.begin() + i);
		}
	}

	for (int i = 0; i < m_player2Pawns.size(); i++)
	{
		if (m_player2Pawns[i].m_coor == coor)
		{
			m_player2Pawns.erase(m_player2Pawns.begin() + i);
		}
	}
}

void Grid::checkForClick()
{
	if (mouseIsPressed())
	{
		for (int r = 0; r < BOARD_SIZE; r++)
		{
			for (int c = 0; c < BOARD_SIZE; c++)
			{
				if (isMouseInRect(m_gridSquares[r][c].rect))
				{
					int2 coor;
					coor.x = r;
					coor.y = c;
				}
			}
		}
	}
}

void Grid::drawGridSquares()
{
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			drawObject(m_gridSquares[r][c]);
		}
	}
}

void Grid::drawPawns()
{
	if (m_selectedPawn != nullptr)
	{
		drawObject(m_drawSelectedPawn);
	}
	
	for (auto& pawn : m_player1Pawns)
	{
		drawObject(pawn);
	}

	for (auto& pawn : m_player2Pawns)
	{
		drawObject(pawn);
	}
}

void Grid::drawCards()
{
	for (int i = 0; i < 2; i++)
	{
		drawObject(*m_player1Cards[i]);
		drawObject(*m_player2Cards[i]);
	}

	if (m_onTurn == 1)
	{
		drawObject(*m_player1nextMove);
	}
	else if(m_onTurn == 2)
	{
		drawObject(*m_player2nextMove);
	}

	if (m_selectedCard != nullptr)
	{
		drawObject(m_drawSelectedCard);
	}

}

void Grid::onHover()
{
	m_hoverGrid = nullptr;
	
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (isMouseInRect(m_gridSquares[r][c].rect))
			{
				m_hoverGrid = &m_gridSquares[r][c];
			}
		}
	}
}

void Grid::drawHover()
{
	if (m_hoverGrid != nullptr)
	{
		m_hover.rect = m_hoverGrid->rect;
		drawObject(m_hover);
	}
}

void Grid::drawAvailableMoves()
{
	for(Drawable* dr : m_availableMoves)
	{
		m_availableMove.rect = dr->rect;
		drawObject(m_availableMove);
	}
}

/*
* Fill the vector of available moves
*/
void Grid::calcAvailableMoves()
{
	m_availableMoves.clear();

	// check if should use this function
	if (m_selectedCard != nullptr && m_selectedPawn != nullptr)
	{
		// get the coor of all possible moves
		for (auto& move : m_selectedCard->data.m_availableMoves)
		{
			int2 tile = move + m_selectedPawn->m_coor;

			// check if we are in the board
			if (tile.x >= 0 && tile.y >= 0 
				&& tile.x < BOARD_SIZE && tile.y < BOARD_SIZE)
			{
				m_availableMoves.push_back(&m_gridSquares[tile.x][tile.y]);
			}
		}
	}
}

void Grid::cardSwitch()
{
	// this function requires a card to be selected
	assert(m_selectedCard != nullptr);

	if (m_onTurn == 1)
	{
		m_player2nextMove->data = m_selectedCard->data;
		m_player2nextMove->texture = m_player2nextMove->data.reversedTexture;
		m_selectedCard->data = m_player1nextMove->data;
		m_selectedCard->texture = m_selectedCard->data.texture;
	}
	else if(m_onTurn == 2)
	{
		m_player1nextMove->data = m_selectedCard->data;
		m_player1nextMove->texture = m_player1nextMove->data.texture;
		m_selectedCard->data = m_player2nextMove->data;
		m_selectedCard->texture = m_selectedCard->data.reversedTexture;
	}

	// flip the moves of the card, that is being passed
	for (auto& move : m_selectedCard->data.m_availableMoves)
	{
		move.y *= -1;
	}
}

/*
* check for valid move when we add entity
* @param coor - the coordinates of the square we are checking
* @return true if the square is free, false if it is not
*/
bool Grid::possMove(int2 coor)
{
	if (m_selectedCard == nullptr || m_selectedPawn == nullptr)
	{
		return false;
	}

	for (auto& move : m_selectedCard->data.m_availableMoves)
	{
		if (m_selectedPawn->m_coor + move == coor)
		{
			return true;
		}
	}

	return false;
}

vector<int> Grid::getRandomIndexes(int start, int finish, int amount)
{
	vector<int> copy;

	for (int i = start; i <= finish; i++)
	{
		copy.push_back(i);
	}

	vector<int> result;

	while (result.size() != amount)
	{
		
		srand(time(NULL));
		int randomIndex = 0 + rand() % copy.size();

		result.push_back(copy[randomIndex]);
		
		copy.erase(copy.begin() + randomIndex);
	}

	return result;
}

void Grid::flipCard(Card* card)
{
	card->texture = card->data.reversedTexture;

	for (auto& move : card->data.m_availableMoves)
	{
		move.y *= -1;
	}
}

int Grid::checkForWinner()
{
	// temple win condition
	const int2 _player1Temple = { 2, 0 };
	const int2 _player2Temple = { 2, 4 };

	for (int i = 0; i < m_player1Pawns.size(); i++)
	{
		if (m_player1Pawns[i].m_coor == _player2Temple)
		{
			return 1;
		}
	}

	for (int i = 0; i < m_player2Pawns.size(); i++)
	{
		if (m_player2Pawns[i].m_coor == _player1Temple)
		{
			return 2;
		}
	}

	// no pawns win condition
	if (m_player1Pawns.size() == 0)
	{
		cout << "no pawns win condition\n";
		return 2;
	}
	else if (m_player2Pawns.size() == 0)
	{
		return 1;
	}

	// no sensei pawn win condition

	bool hasSensei;

	hasSensei = false;
	for (int i = 0; i < m_player1Pawns.size(); i++)
	{
		if (m_player1Pawns[i].isSensei == true)
		{
			hasSensei = true;
			break;
		}
	}
	if (hasSensei == false)
	{
		return 2;
	}

	hasSensei = false;
	for (int i = 0; i < m_player2Pawns.size(); i++)
	{
		if (m_player2Pawns[i].isSensei == true)
		{
			hasSensei = true;
			break;
		}
	}
	if (hasSensei == false)
	{
		return 1;
	}

	return 0;
}

void Grid::easyBot() {

	vector<pair<int2, pair<int,int>>> possMoves;
	for (int i = 0; i < m_player2Pawns.size(); i++)
	{
		for (int card = 0; card < 2; card++)
		{
			for (auto& move : m_player2Cards[card]->data.m_availableMoves)
			{
				int2 tile = move + m_player2Pawns[i].m_coor;

				// check if we are in the board
				if (tile.x >= 0 && tile.y >= 0
					&& tile.x < BOARD_SIZE && tile.y < BOARD_SIZE)
				{
					bool pawnThere = false;
					for (int k = 0; k < m_player2Pawns.size(); k++)
					{
						if (m_player2Pawns[k].m_coor == tile)
						{
							pawnThere = true;
							break;
						}
					}
					if(!pawnThere) possMoves.push_back(make_pair(tile, make_pair(i, card)));
				}
			}
		}
	}

	int idx = rand() % possMoves.size();
	int r = possMoves[idx].first.x;
	int c = possMoves[idx].first.y;
	int pawn = possMoves[idx].second.first;
	int card = possMoves[idx].second.second;

	m_selectedPawn = & m_player2Pawns[pawn];
	m_selectedCard = m_player2Cards[card];
	m_drawSelectedCard.rect = m_selectedCard->rect;

	killPawn({r, c});
	m_selectedPawn->m_coor.x = r;
	m_selectedPawn->m_coor.y = c;

	m_selectedPawn->rect = m_gridSquares[r][c].rect;

	cardSwitch();

	m_onTurn = (m_onTurn == 1) + 1;

	m_selectedPawn = nullptr;
	m_selectedCard = nullptr;
}

void Grid::hardBot() {

	set<AImove> allMoves;
	/*  Priorities:
		7 - winning move
		6 - a move that saves my sensei and takes a pawn
		5 - a move that saves my sensei
		4 - a move that saves my pawn and takes a pawn
		3 - a move that saves my pawn
		2 - a move that takes a pawn
		1 - a move that does not threathen my pawn
		0 - just a move
	*/ 

	// determine which tiles would be deadly for me to step on
	set<pair<int,int>> dangerousTiles;
	for (int k = 0; k < m_player1Pawns.size(); k++)
	{
		for (int l = 0; l < 2; l++)
		{
			for (auto& move2 : m_player1Cards[l]->data.m_availableMoves)
			{
				int2 tile2 = move2 + m_player1Pawns[k].m_coor;
				dangerousTiles.insert(make_pair(tile2.x, tile2.y));
			}
		}
	}

	for (int i = 0; i < m_player2Pawns.size(); i++)
	{
		// check if pawn is threatened right now
		bool isThreatenedNow = false;
		auto pos = dangerousTiles.find(make_pair(m_player2Pawns[i].m_coor.x, m_player2Pawns[i].m_coor.y));
		if (pos != dangerousTiles.end()) isThreatenedNow = true;
		for (int card = 0; card < 2; card++)
		{
			for (auto& move : m_player2Cards[card]->data.m_availableMoves)
			{
				int2 tile = move + m_player2Pawns[i].m_coor;

				// check if we are in the board
				if (tile.x >= 0 && tile.y >= 0
					&& tile.x < BOARD_SIZE && tile.y < BOARD_SIZE)
				{

					// check if my pawn is on this tile
					bool pawnThere = false;
					for (int k = 0; k < m_player2Pawns.size(); k++)
					{
						if (m_player2Pawns[k].m_coor == tile)
						{
							pawnThere = true;
							break;
						}
					}
					if (!pawnThere)
					{
						bool pawnThere = false;
						for (int k = 0; k < m_player1Pawns.size(); k++)
						{
							// check if this move can threaten my pawn
							bool isThreatened = false;
							auto pos = dangerousTiles.find(make_pair(tile.x, tile.y));
							if (pos != dangerousTiles.end()) isThreatened = true;

							// check if with this move can I can step in temple
							if (tile.x == 2 && tile.y == 0)
							{
								allMoves.insert(AImove(7, tile, i, card));
								continue;
							}

							// check if this move can kill a pawn
							if (m_player1Pawns[k].m_coor == tile)
							{
								if (m_player1Pawns[k].isSensei)
								{
									allMoves.insert(AImove(7, tile, i, card));
									continue;
								}
								if ((m_player2Pawns[i].isSensei && !isThreatened) || !m_player2Pawns[i].isSensei)
								{
									pawnThere = true;
									if (isThreatenedNow)
									{
										if(m_player2Pawns[i].isSensei)
											allMoves.insert(AImove(6, tile, i, card));
										else
											allMoves.insert(AImove(4, tile, i, card));
									}
									allMoves.insert(AImove(2, tile, i, card));
									continue;
								}
							}

							// check if this move would do absolutely no harm to any team
							else if (!isThreatened)
							{
								pawnThere = true;
								if (isThreatenedNow)
								{
									if (m_player2Pawns[i].isSensei)
										allMoves.insert(AImove(5, tile, i, card));
									else
										allMoves.insert(AImove(3, tile, i, card));
								}
								allMoves.insert(AImove(1, tile, i, card));
								continue;
							}
						}
						//add move as possible although it might be dangerous
						allMoves.insert(AImove(0, tile, i, card));
					}
				}
			}
		}
	}

	int r, c, pawn, card;
	auto idx = allMoves.end();
	idx --;
	r = (*idx).tile.x;
	c = (*idx).tile.y;
	pawn = (*idx).pawn;
	card = (*idx).card;

	m_selectedPawn = & m_player2Pawns[pawn];
	m_selectedCard = m_player2Cards[card];
	m_drawSelectedCard.rect = m_selectedCard->rect;

	killPawn({r, c});
	m_selectedPawn->m_coor.x = r;
	m_selectedPawn->m_coor.y = c;

	m_selectedPawn->rect = m_gridSquares[r][c].rect;

	cardSwitch();

	m_onTurn = (m_onTurn == 1) + 1;

	m_hoverGrid = nullptr;
	m_selectedPawn = nullptr;
	m_selectedCard = nullptr;
	m_selected = false;
}

void Grid::update()
{
	if (!winner)
	{
		onHover();

		if (wait) { SDL_Delay(2000); wait = false; }

		if (m_gameType == 1 && m_onTurn == 2)
		{
			SDL_Delay(1500);
			easyBot();
		}
		else if (m_gameType == 2 && m_onTurn == 2)
		{
			SDL_Delay(1000);
			hardBot();
			wait = true;
		}

		checkForClick();
		select();
		calcAvailableMoves();

		winner = checkForWinner();
		
		if (winner)
		{
			if (m_gameType != 0 && winner != 1)
			{
				winner *= -1;
			}
			
			world.m_stateManager.changeGameState(GAME_STATE::WIN_SCREEN);
			
			m_player1Pawns.clear();
			m_player2Pawns.clear();
		}
	}
}
