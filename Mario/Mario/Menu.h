#pragma once

#ifndef _MENU
#define _MENU

#include "Library.h"
#include "MenuOption.h"

class Menu
{
public:
	vector<MenuOption*> menuOption;

	int activeMenuOption;
	int numberOfMenuOption;

	Menu();
	~Menu();

	virtual void Update();
	virtual void Draw(sf::RenderWindow& window);

	virtual void UpdateActiveButton(int number);
};

#endif
