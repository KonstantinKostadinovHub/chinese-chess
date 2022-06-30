#pragma once

#include "Presenter.h"
#include "StateManager.h"
#include "InputManager.h"
#include "SoundManager.h"

class World
{
public:
	World();
	~World();

	Presenter m_presenter;
	StateManager m_stateManager;
	InputManager m_inputManager;
	SoundManager m_soundManager;
	ConfigManager m_config;

	void init();
	void run();
	void destroy();
	
	bool isRunning();
private:
	bool m_isRunning;
};