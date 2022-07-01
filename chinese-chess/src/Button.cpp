#include "Button.h"

#include "World.h"

extern World world;

Button::Button()
{
	m_texture = nullptr;
}

Button::Button(const Button* model)
{
	m_startRect = model->m_startRect;
	m_rect = m_startRect;
	m_texture = model->m_texture;
	m_maxIncrease = model->m_maxIncrease;
	m_increasePerFrame = model->m_increasePerFrame;
}

Button::~Button()
{
	m_texture = nullptr;

	m_renderer = nullptr;
}

void Button::init(string configFile, string folder)
{
	m_renderer = world.m_presenter.getRenderer();
	m_inputManager = &world.m_inputManager;

	configFile = CONFIG_FOLDER + folder + configFile;

	fstream stream;
	stream.open(configFile);

	string texturePath;
	string tmp;

	stream >> tmp >> texturePath;
	stream >> tmp >> m_startRect.x >> m_startRect.y >> m_startRect.w >> m_startRect.h;

	stream >> tmp >> m_maxIncrease;
	stream >> tmp >> m_increasePerFrame;

	stream.close();

	texturePath = folder + texturePath;

	m_texture = LoadTexture(texturePath, m_renderer);

	m_rect = m_startRect;

	m_increasePerVertex.x = float(m_rect.w) / float(max(m_rect.w, m_rect.h));
	m_increasePerVertex.y = float(m_rect.h) / float(max(m_rect.w, m_rect.h));
}

void Button::destroy()
{
	SDL_DestroyTexture(m_texture);
}

void Button::update()
{
	m_isClicked = false;

	if (isMouseInRect(m_rect))
	{
		hover();

		if (mouseIsPressed())
		{
			m_isClicked = true;
		}
	}
	else
	{
		defaultState();
	}

	m_rect.x = m_startRect.x - m_increasePerVertex.x * static_cast<int>(m_currIncrease);
	m_rect.y = m_startRect.y - m_increasePerVertex.y * static_cast<int>(m_currIncrease);
	m_rect.w = m_startRect.w + m_increasePerVertex.x * 2.0 * static_cast<int>(m_currIncrease);
	m_rect.h = m_startRect.h + m_increasePerVertex.y * 2.0 * static_cast<int>(m_currIncrease);
}

void Button::draw()
{
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_rect);
}

void Button::hover()
{
	if (m_currIncrease < m_maxIncrease)
	{
		m_currIncrease += m_increasePerFrame;
	}
	else
	{
		m_currIncrease = m_maxIncrease;
	}
}

void Button::defaultState()
{
	if (m_currIncrease > 0)
	{
		m_currIncrease -= m_increasePerFrame;
	}
	else
	{
		m_currIncrease = 0;
	}
}

SDL_Rect Button::getRect()
{
	return m_rect;
}