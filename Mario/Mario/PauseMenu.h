#pragma once

#ifndef _PAUSEMENU
#define _PAUSEMENU

#include "Menu.h"

class PauseMenu : public Menu
{
private:
	sf::RectangleShape pause;
public:
	PauseMenu();
	~PauseMenu();

	void Update();
	void Draw(sf::RenderWindow& window);

	void Enter();
	void Escape();

	void UpdateActiveButton(int id);
};

#endif
