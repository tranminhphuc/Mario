#include "PauseMenu.h"
#include "Windows.h"

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
	pause.setFillColor(sf::Color(4, 4, 4, 255));
	pause.setSize(sf::Vector2f(pause.getSize().x + 1, pause.getSize().y + 1));
	pause.move(-2, -2);
	pause.setFillColor(sf::Color(255, 255, 255, 255));
	pause.setSize(sf::Vector2f(pause.getSize().x - 1, pause.getSize().y - 1));
	pause.move(2, 2);

	for (int i = 0; i < menuOption.size(); i++)
	{
		if (i == activeMenuOption)
			Window::GetText()->DrawCenterX(window, menuOption[i]->GetText(), menuOption[i]->GetY(), 255, 255, 255);
		else
			Window::GetText()->DrawCenterX(window, menuOption[i]->GetText(), menuOption[i]->GetY(), 90, 90, 90);
	}

	Window::GetMap()->SetBackGroundColor(window);
}

void PauseMenu::Enter()
{
	switch (activeMenuOption)
	{
	case 0:
		Window::GetMenuManager()->SetView(Window::GetMenuManager()->GamePlay);
		break;
	case 1:
		Window::GetMenuManager()->GetOptionMenu()->SetEscapeToMainMenu(false);
		Window::GetMenuManager()->ResetActiveOption(Window::GetMenuManager()->GameOption);
		Window::GetMenuManager()->SetView(Window::GetMenuManager()->GameOption);
		break;
	case 2:
		Window::GetMap()->ResetGameData();
		Window::GetMenuManager()->SetView(Window::GetMenuManager()->MenuGame);
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
