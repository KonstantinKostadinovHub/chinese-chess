#include "Menu.h"
#include "World.h"

extern World world;

Menu::Menu()
{
}

Menu::~Menu()
{
	
}

void Menu::init()
{
	fstream stream;

	string tmp, img, exitBtnPath, onePlayerBtn, twoPlayersBtn;

	stream.open(CONFIG_FOLDER + MENU_FOLDER + "menu.txt");

	stream >> tmp >> img;
	stream >> tmp >> exitBtnPath;
	stream >> tmp >> onePlayerBtn;
	stream >> tmp >> twoPlayersBtn;

	stream.close();

	m_menuTexture = loadTexture(MENU_FOLDER + img);

	m_exitBtn.init(exitBtnPath, MENU_FOLDER);
	m_onePlayerBtn.init(onePlayerBtn, MENU_FOLDER);
	m_twoPlayersBtn.init(twoPlayersBtn, MENU_FOLDER);
}

void Menu::run()
{	
	drawObject(m_menuTexture);

	m_onePlayerBtn.update();
	m_onePlayerBtn.draw();
	
	m_twoPlayersBtn.update();
	m_twoPlayersBtn.draw();
	
	m_exitBtn.update();
	m_exitBtn.draw();

	if (m_popUp != nullptr)
	{
		m_popUp->run();

		if (m_popUp->m_easyBtn->m_isClicked)
		{
			world.m_stateManager.m_game->m_grid.m_gameType = 1;
			
			world.m_stateManager.changeGameState(GAME_STATE::GAME);
		}

		if (m_popUp->m_hardBtn->m_isClicked)
		{
			world.m_stateManager.m_game->m_grid.m_gameType = 2;
			
			world.m_stateManager.changeGameState(GAME_STATE::GAME);
		}
	}
	
	if (mouseIsPressed())
	{
		if (isMouseInRect(m_twoPlayersBtn.getRect()))
		{
			world.m_stateManager.m_game->m_grid.m_gameType = 0;
			
			world.m_stateManager.changeGameState(GAME_STATE::GAME);

			return;
		}

		if (isMouseInRect(m_onePlayerBtn.getRect()))
		{			
			m_popUp = new PopUp();

			m_popUp->init();
			
			return;
		}
		
		if (isMouseInRect(m_exitBtn.getRect()))
		{
			world.m_stateManager.changeGameState(GAME_STATE::NONE);

			return;
		}
	}
}

void Menu::destroy()
{
	m_onePlayerBtn.destroy();
	m_twoPlayersBtn.destroy();
	m_exitBtn.destroy();

	SDL_DestroyTexture(m_menuTexture);
}