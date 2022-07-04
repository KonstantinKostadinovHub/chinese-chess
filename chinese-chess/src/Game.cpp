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
}

void Game::destroy()
{
	m_grid.destroy();
}

void Game::run()
{
	m_grid.update();
	m_grid.draw();
}