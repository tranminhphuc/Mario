#pragma once

#ifndef _MENUMANAGER
#define _MENUMANAGER

#include "MainMenu.h"
#include "LoadingMenu.h"
#include "OptionMenu.h"
#include "PauseMenu.h"
#include "Library.h"

class MenuManager
{
private:
	MainMenu* mainMenu;
	LoadingMenu* loadingMenu;
	OptionMenu* optionMenu;
	PauseMenu* pauseMenu;

	enum GameState
	{
		MainMenuGame,
		GamePlay,
		GameLoading,
		GameOption,
		Pause
	};

	GameState currentGameState;
public:
	MenuManager();
	~MenuManager();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window);

	void SetBackGroundColor(sf::RenderWindow& window);

	void Enter();
	void Escape();

	void SetKey(int id);
	void keyPressed(int id);
	void ResetActiveOption(GameState id);

	int GetState();
	void SetState(GameState ID);
};

#endif
