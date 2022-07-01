#include "World.h"

World::World()
{
	m_isRunning = true;
}

World::~World()
{
}

void World::init()
{
	m_presenter.init();
	m_config.load();
	m_stateManager.init(GAME_STATE::TITLE_SCREEN);
	m_soundManager.init();
}

void World::run()
{
	m_inputManager.handleInput();

	m_stateManager.run();

	m_presenter.draw();
}

// call destroy for all classes to prevent memory leak
void World::destroy()
{
	m_soundManager.destroy();

	SDL_DestroyRenderer(m_presenter.m_main_renderer);

	SDL_DestroyWindow(m_presenter.m_main_window);
}

bool World::isRunning()
{
	return m_isRunning;
}
