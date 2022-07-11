#include "PopUp.h"
#include "World.h"

PopUp::PopUp()
{
	m_easyBtn = new Button();
	m_hardBtn = new Button();
}

PopUp::~PopUp()
{

}

void PopUp::init()
{
	fstream stream;

	string tmp, easyBtn, hardBtn, difficultyImg;

	stream.open(CONFIG_FOLDER + MENU_FOLDER + "popUp.txt");

	stream >> tmp >> easyBtn;
	stream >> tmp >> hardBtn;
	stream >> tmp >> m_difficulty.rect.x >> m_difficulty.rect.y >> m_difficulty.rect.w >> m_difficulty.rect.h;
	stream >> tmp >> difficultyImg;

	stream.close();

	m_easyBtn->init(easyBtn, MENU_FOLDER);
	m_hardBtn->init(hardBtn, MENU_FOLDER);

	m_difficulty.texture = loadTexture(MENU_FOLDER + difficultyImg);
}

void PopUp::run()
{
	drawObject(m_difficulty);

	m_easyBtn->update();
	m_easyBtn->draw();

	m_hardBtn->update();
	m_hardBtn->draw();
}

void PopUp::destroy()
{
	SDL_DestroyTexture(m_difficulty.texture);

	m_easyBtn->destroy();
	m_hardBtn->destroy();
}
