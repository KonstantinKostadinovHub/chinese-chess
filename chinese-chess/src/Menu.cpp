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

	string tmp, img, playBtnPath, exitBtnPath;

	stream.open(CONFIG_FOLDER + MENU_FOLDER + "menu.txt");

	stream >> tmp >> img;
	stream >> tmp >> playBtnPath;
	stream >> tmp >> exitBtnPath;

	stream.close();

	m_menuTexture = loadTexture(MENU_FOLDER + img);

	m_playBtn.init(playBtnPath, MENU_FOLDER);
	m_exitBtn.init(exitBtnPath, MENU_FOLDER);
}

void Menu::run()
{	
	drawObject(m_menuTexture);

	m_playBtn.update();
	m_playBtn.draw();
	
	m_exitBtn.update();
	m_exitBtn.draw();

	if (mouseIsPressed())
	{
		if (isMouseInRect(m_playBtn.getRect()))
		{
			world.m_soundManager.playSound(SOUND::BUTTON_CLICK);

			world.m_stateManager.changeGameState(GAME_STATE::GAME);

			return;
		}
		else if (isMouseInRect(m_exitBtn.getRect()))
		{
			world.m_soundManager.playSound(SOUND::BUTTON_CLICK);

			world.m_stateManager.changeGameState(GAME_STATE::NONE);

			return;
		}
	}
}

void Menu::destroy()
{
	m_playBtn.destroy();
	m_exitBtn.destroy();

	SDL_DestroyTexture(m_menuTexture);
}