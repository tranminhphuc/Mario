#pragma once

#ifndef _MAINMENU
#define _MAINMENU

#include "Menu.h"

class MainMenu : public Menu
{
private:
	bool selectWorld;
	int activeWorldID, activeSecondWorldID;

	sf::RectangleShape selectWorldLabel;
public:
	MainMenu();
	~MainMenu();

	void Update();
	void Draw(sf::RenderWindow& window);

	void UpdateActiveButton(int number);

	void Enter();
	void Escape();
};

#endif
