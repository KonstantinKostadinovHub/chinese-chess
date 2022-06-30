#include "Grid.h"

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

void Grid::load()
{

	int2 coordinates; // from where do we start

	string temp , player1OnTurn, player2OnTurn, tutorailImg;
	fstream stream;

	int squareSize;
	int2 cardDim;

	m_player1Cards[0] = new Card;
	m_player1Cards[1] = new Card;
	m_player2Cards[0] = new Card;
	m_player2Cards[1] = new Card;
	m_player1nextMove = new Card;
	m_player2nextMove = new Card;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "grid.txt");

	stream >> temp >> squareSize;

	stream >> temp >> m_player1OnTurn.rect.x >> m_player1OnTurn.rect.y >> m_player1OnTurn.rect.w >> m_player1OnTurn.rect.h;
	stream >> temp >> player1OnTurn >> player2OnTurn;
	stream >> temp >> m_tutorial.rect.x >> m_tutorial.rect.y >> m_tutorial.rect.w >> m_tutorial.rect.h;
	stream >> temp >> tutorailImg;

	stream >> temp >> cardDim.x >> cardDim.y;

	stream >> temp >> temp;
	m_player1Cards[0]->texture = loadTexture(GAME_FOLDER + temp);
	stream >> temp >> m_player1Cards[0]->rect.x >> m_player1Cards[0]->rect.y;
	m_player1Cards[0]->rect.w = cardDim.x;
	m_player1Cards[0]->rect.h = cardDim.y;

	stream >> temp >> temp;
	m_player1Cards[1]->texture = loadTexture(GAME_FOLDER + temp);
	stream >> temp >> m_player1Cards[1]->rect.x >> m_player1Cards[1]->rect.y;
	m_player1Cards[1]->rect.w = cardDim.x;
	m_player1Cards[1]->rect.h = cardDim.y;

	stream >> temp >> temp;
	m_player2Cards[0]->texture = loadTexture(GAME_FOLDER + temp);
	stream >> temp >> m_player2Cards[0]->rect.x >> m_player2Cards[0]->rect.y;
	m_player2Cards[0]->rect.w = cardDim.x;
	m_player2Cards[0]->rect.h = cardDim.y;

	stream >> temp >> temp;
	m_player2Cards[1]->texture = loadTexture(GAME_FOLDER + temp);
	stream >> temp >> m_player2Cards[1]->rect.x >> m_player2Cards[1]->rect.y;
	m_player2Cards[1]->rect.w = cardDim.x;
	m_player2Cards[1]->rect.h = cardDim.y;

	stream.close();

	m_player1Cards[0]->m_moves = { {0, -1} };
	m_player1Cards[1]->m_moves = { {0, -2} };
	m_player2Cards[0]->m_moves = { {1, -2} };
	m_player2Cards[1]->m_moves = { {2, -2} };
	m_player1nextMove->m_moves = { {2, 0} };
	m_player2nextMove->m_moves = { {-2, 0} };

	m_player2OnTurn.rect = m_player1OnTurn.rect;

	m_player1OnTurn.texture = loadTexture(GAME_FOLDER + player1OnTurn);
	m_player2OnTurn.texture = loadTexture(GAME_FOLDER + player2OnTurn);
	m_tutorial.texture = loadTexture(GAME_FOLDER + tutorailImg);
	
	m_drawTutorial = false;
	
	m_availableMove.texture = loadTexture(GAME_FOLDER + "unavailableTile.bmp");
	m_hover.texture = loadTexture(GAME_FOLDER + "gridPossMove.bmp");
	
	SDL_Texture* modelSquareTexture;
	modelSquareTexture = loadTexture(GAME_FOLDER + "tile.bmp");
	
	m_background = loadTexture(GAME_FOLDER + "background.bmp");

	coordinates.x = (Presenter::m_SCREEN_WIDTH - squareSize * BOARD_SIZE) / 2;
	coordinates.y = (Presenter::m_SCREEN_HEIGHT - squareSize * BOARD_SIZE) / 2;	
		
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			m_gridSquares[r][c].rect = { c * squareSize + coordinates.x,
				r * squareSize + coordinates.y, 
				squareSize, 
				squareSize};
			
			m_gridSquares[r][c].texture = modelSquareTexture;
		}
	}

	loadPawns();
	loadCards();
}

void Grid::draw()
{
	drawObject(m_background);

	drawGridSquares();

	drawAvailableMoves();

	drawPawns();

	drawHover();
	
	if (m_drawTutorial)
	{
		drawObject(m_tutorial);
	}
	
	if (m_onTurn == 1)
	{
		drawObject(m_player1OnTurn);
	}
	else if(m_onTurn == 2)
	{
		drawObject(m_player2OnTurn);
	}
}

/*
* changes the m_winner param, that is later used by WinScreen.h
*/
void Grid::winCondition()
{
	
}

void Grid::destroy()
{
/*
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities[i];
	}
	m_entities.clear();
*/
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
		buff.texture = ConfigManager::m_pawn1;
		buff.m_owner = 1;
		m_player1Pawns.push_back(buff);

		buff.m_coor.x = i;
		buff.m_coor.y = BOARD_SIZE - 1;
		buff.rect = m_gridSquares[i][BOARD_SIZE - 1].rect;
		buff.texture = ConfigManager::m_pawn2;
		buff.m_owner = 2;
		m_player2Pawns.push_back(buff);
	}
}

void Grid::loadCards()
{

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
			}
		}
	}
	else if (m_onTurn == 2)
	{
		for (int i = 0; i < m_player2Pawns.size(); i++)
		{
			if (isMouseInRect(m_player2Pawns[i].rect))
			{
				m_selectedPawn = &m_player2Pawns[i];
				selected = true;
			}
		}
	}

	if (!selected)
	{
		m_selected = true;
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

							m_onTurn = (m_onTurn == 1) + 1;

							m_selectedPawn = nullptr;
						}
					}
				}
			}
		}
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
				m_selected = true;
			}
		}
	}
	else if (m_onTurn == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			if (isMouseInRect(m_player2Cards[i]->rect))
			{
				m_selectedCard = m_player2Cards[i];
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
		/*
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_entities[i]->getRect()))
			{
				m_currentEntity = m_entities[i];
				m_lastEntityCoordinates = centerOfRect(m_entities[i]->getRect());
			}
		}
		*/
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
	for (auto& pawn : m_player1Pawns)
	{
		drawObject(pawn);
	}

	for (auto& pawn : m_player2Pawns)
	{
		drawObject(pawn);
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

void Grid::calcAvailableMoves()
{
	m_availableMoves.clear();
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			//TODO: add check when we add the cards
			if (true)
			{
				m_availableMoves.push_back(&m_gridSquares[r][c]);
			}
		}
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
	for (auto& move : m_selectedCard->m_moves)
	{
		if (m_selectedPawn->m_coor + move == coor)
		{
			return true;
		}
	}
	return false;
}

void Grid::update()
{
	onHover();

	checkForClick();
	select();
	calcAvailableMoves();

	winCondition();
}
