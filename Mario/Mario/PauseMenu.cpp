#include "PauseMenu.h"
#include "Windows.h"
#include "Game.h"

PauseMenu::PauseMenu()
{
	pause.setPosition(220, 140);
	pause.setSize(sf::Vector2f(360, 142));

	menuOption.push_back(new MenuOption("RESUME", 0, 156));
	menuOption.push_back(new MenuOption("OPTION", 0, 180));
	menuOption.push_back(new MenuOption("QUIT TO MENU", 0, 228));
	menuOption.push_back(new MenuOption("QUIT TO DESKTOP", 0, 252));

	numberOfMenuOption = (int)menuOption.size();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update()
{
}

void PauseMenu::Draw(sf::RenderWindow & window)
{
}

void PauseMenu::Enter()
{
	switch (activeMenuOption)
	{
	case 0:
		Game::GetMenuManager()->SetView(Game::GetMenuManager()->GamePlay);
		break;
	case 1:
		Game::GetMenuManager()->GetOptionMenu()->SetEscapeToMainMenu(false);
		Game::GetMenuManager()->ResetActiveOption(Game::GetMenuManager()->GameOption);
		Game::GetMenuManager()->SetView(Game::GetMenuManager()->GameOption);
		break;
	case 2:
		Window::GetMap()->ResetGameData();
		Game::GetMenuManager()->SetView(Game::GetMenuManager()->MenuGame);
		break;
	case 3:
		//......
		break;
	}
}

void PauseMenu::Escape()
{
	//......
}

void PauseMenu::UpdateActiveButton(int id)
{
	Menu::UpdateActiveButton(id);
}
