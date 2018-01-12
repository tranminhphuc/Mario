#include "MainMenu.h"

MainMenu::MainMenu()
{
	menuOption.push_back(new MenuOption("1 PLAYER GAME", 178, 276));
	menuOption.push_back(new MenuOption("OPTIONS", 222, 308));
	menuOption.push_back(new MenuOption("ABOUT", 237, 340));

	numberOfMenuOption = (int)menuOption.size();
	selectWorld = false;
	activeWorldID = activeSecondWorldID = 0;

	selectWorldLabel.left = 122;
	selectWorldLabel.top = 280;
	selectWorldLabel.width = 306;
	selectWorldLabel.height = 72;
}

MainMenu::~MainMenu()
{
}

void MainMenu::Update()
{
}

void MainMenu::Draw(sf::RenderWindow & window)
{
}

void MainMenu::UpdateActiveButton(int number)
{
}

void MainMenu::Enter()
{
}

void MainMenu::Escape()
{
}
