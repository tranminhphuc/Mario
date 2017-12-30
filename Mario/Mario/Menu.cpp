#include "Menu.h"

Menu::Menu()
{
	activeMenuOption = 0;
}

Menu::~Menu()
{
}

void Menu::Update()
{
}

void Menu::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < menuOption.size(); i++)
	{

	}
}

void Menu::UpdateActiveButton(int number)
{
	switch (number)
	{
	case 0:
		if (activeMenuOption < 1)
			activeMenuOption = numberOfMenuOption - 1;
		else
			activeMenuOption--;
		break;
	case 2:
		if (activeMenuOption >= numberOfMenuOption - 1)
			activeMenuOption = 0;
		else
			activeMenuOption++;
		break;
	default:
		break;
	}
}
