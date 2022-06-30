#include "Card.h"
#include "Presenter.h"

Card::Card()
{

}

Card::~Card()
{

}

void Card::init(string configFile)
{
	fstream stream;

	string tmp, img;

	stream.open(CONFIG_FOLDER + CARDS_FOLDER + configFile);

	stream >> tmp >> rect.w >> rect.h;
	stream >> tmp >> img;

	while (!stream.eof())
	{
		int2 coor;

		stream >> coor.x >> coor.y;

		m_moves.push_back(coor);
	}

	stream.close();

	texture = loadTexture(CARDS_FOLDER + img);
}

void Card::destroy()
{
	SDL_DestroyTexture(texture);
}
