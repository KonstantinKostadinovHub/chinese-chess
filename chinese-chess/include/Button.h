#pragma once

#include <fstream>

#include <SDL.h>

#include "defines.h"
#include "Engine.h"
#include "InputManager.h"

class Button
{
public:
	Button();
	// Providing the option to create a button by giving it a model
	Button(const Button* model);
	virtual ~Button();

	SDL_Renderer* m_renderer;
	InputManager* m_inputManager;

	SDL_Rect m_rect;
	SDL_Rect m_startRect;

	SDL_Texture* m_texture;

	float2 m_increasePerVertex;

	int m_maxIncrease;
	float m_currIncrease;
	float m_increasePerFrame;
	bool m_isClicked;

	// passing the path (searching in CONFIG)
	virtual void init(string configFile, string folder);
	virtual void destroy();

	virtual void update();
	virtual void draw();

	void hover();
	void defaultState();

	SDL_Rect getRect();
};