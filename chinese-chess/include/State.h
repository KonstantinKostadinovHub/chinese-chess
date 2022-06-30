#pragma once

/* \brief abstract class used for each state of the game
*/
class State
{
public:
	State();
	virtual	~State();


	/*
	* !!! Don't add configFiles in this function !!!
	* For example: in the Lobby we don't need an init
	* We have spaceship class that is responsible for all the
	* data that must be loaded from configFiles
	*/
	virtual void init() = 0;
	/*
	* The main "update" function
	*/
	virtual void run() = 0;
	/*
	* Clear all the data that the state has
	*/
	virtual void destroy() = 0;
};