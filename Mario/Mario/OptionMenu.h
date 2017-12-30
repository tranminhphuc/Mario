#pragma once

#ifndef _OPTIONMENU
#define _OPTIONMENU

#include "Menu.h"

class OptionMenu : public Menu
{
private:
	sf::RectangleShape rect;
	sf::RectangleShape setKeyRect;
	sf::RectangleShape volumeChange;
	sf::RectangleShape volume;

	bool setKey, resetKey;
	bool escapeToMainMenu;
public:
	OptionMenu();
	~OptionMenu();

	void Update();
	void Draw(sf::RenderWindow& window);

	void Enter();
	void Escape();
	void SetKey(int keyID);

	void UpdateActiveButton(int id);
};

#endif
