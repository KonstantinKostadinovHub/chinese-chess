#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
	m_grid.load();
	//Entity::m_grid = &m_grid;
}

void Game::destroy()
{
	
}

void Game::run()
{
	m_grid.update();
	m_grid.draw();

}

