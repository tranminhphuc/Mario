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
public:
	enum GameState
	{
		MenuGame,
		GamePlay,
		GameLoading,
		GameOption,
		Pause
	};
	GameState currentGameState;

	MenuManager();
	~MenuManager();

	void Update();
	void Draw(sf::RenderWindow& window);

	void SetBackGroundColor(sf::RenderWindow& window);

	void Enter();
	void Escape();

	//sua nut
	void SetKey(int id);
	//nut da an
	void keyPressed(int id);
	//quay ve lua chon dau tien
	void ResetActiveOption(GameState id);

	int GetView();
	void SetView(GameState ID);

	LoadingMenu* GetLoadingMenu();
	OptionMenu* GetOptionMenu();
};

#endif
