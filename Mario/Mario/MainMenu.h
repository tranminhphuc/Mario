#pragma once

#ifndef _MAINMENU
#define _MAINMENU

#include "Menu.h"

class MainMenu : public Menu
{
private:
	//chon level
	bool selectWorld;
	//thay doi level 
	int activeWorldID, activeSecondWorldID;

	sf::IntRect selectWorldLabel;
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
