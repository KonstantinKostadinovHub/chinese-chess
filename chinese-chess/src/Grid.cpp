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

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "grid.txt");

	stream >> temp >> squareSize;

	stream >> temp >> m_player1OnTurn.rect.x >> m_player1OnTurn.rect.y >> m_player1OnTurn.rect.w >> m_player1OnTurn.rect.h;
	stream >> temp >> player1OnTurn >> player2OnTurn;
	stream >> temp >> m_tutorial.rect.x >> m_tutorial.rect.y >> m_tutorial.rect.w >> m_tutorial.rect.h;
	stream >> temp >> tutorailImg;
	
	stream.close();

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
		D(buff.texture);
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
		D(pawn.rect.x);
		D(pawn.rect.w);
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
	if (inGrid(coor, BOARD_SIZE, BOARD_SIZE))
	{
		return true;
	}
	return false;
}

void Grid::update()
{
	onHover();

	checkForClick();
	calcAvailableMoves();

	winCondition();
}
