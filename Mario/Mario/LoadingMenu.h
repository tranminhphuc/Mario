#pragma once

#ifndef _LOADINGMENU
#define _LOADINGMENU

#include "Menu.h"

class LoadingMenu : public Menu
{
private:
	unsigned int time;
public:
	bool loading;

	LoadingMenu();
	~LoadingMenu();

	void Update();
	void Draw(sf::RenderWindow& window);

	void UpdateTime();
};

#endif
