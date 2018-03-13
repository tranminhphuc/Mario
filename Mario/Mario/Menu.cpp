#include "Menu.h"
#include "Windows.h"
#include "Game.h"

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

void Menu::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < menuOption.size(); i++)
	{
		Window::GetText()->Draw(window, menuOption[i]->GetText(), menuOption[i]->GetX(), menuOption[i]->GetY());
	}
}

void Menu::UpdateActiveButton(int number)
{
	switch (number)
	{
	case Window::Up:
		if (activeMenuOption < 1)
			activeMenuOption = numberOfMenuOption - 1;
		else
			activeMenuOption--;
		break;
	case Window::Down:
		if (activeMenuOption >= numberOfMenuOption - 1)
			activeMenuOption = 0;
		else
			activeMenuOption++;
		break;
	default:
		break;
	}
}
