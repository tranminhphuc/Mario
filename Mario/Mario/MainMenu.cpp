#include "MainMenu.h"
#include "Windows.h"
#include "Game.h"

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
	Menu::Update();
}

void MainMenu::Draw(sf::RenderWindow & window)
{
}

void MainMenu::UpdateActiveButton(int number)
{
	switch (number)
	{
	//0 di chuyen len(Up, w), 2 di chuyen xuong(Down, s)
	case 0 : case 2:
		if (!selectWorld)
		{
			Menu::UpdateActiveButton(number);
		}
		else
		{
			switch (number)
			{
			case 0:
				if (activeSecondWorldID < 1)
					activeSecondWorldID = 3;
				else
					activeSecondWorldID--;
				break;
			case 2:
				if (activeSecondWorldID > 2)
					activeSecondWorldID = 0;
				else
					activeSecondWorldID++;
				break;
			}
		}
		break;
	//1 di chuyen sang trai(Left, a)
	case 1:
		if (selectWorld)
		{
			if (activeWorldID < 7)
				activeWorldID++;
			else
				activeWorldID = 0;
		}
		break;
	//3 di chuyen sang phai(Right, d)
	case 3:
		if (selectWorld)
		{
			if (activeWorldID > 0)
				activeWorldID--;
			else
				activeWorldID = 7;
		}
		break;
	}
}

void MainMenu::Enter()
{
	switch (activeMenuOption)
	{
	case 0:
		if (!selectWorld)
		{
			selectWorld = true;
		}
		else
		{
			Game::GetMenuManager()->GetLoadingMenu()->UpdateTime();
			Window::GetMap()->ResetGameData();
			Window::GetMap()->SetLevel(activeWorldID * 4 + activeSecondWorldID);
			Game::GetMenuManager()->SetView(Game::GetMenuManager()->GameLoading);
			Game::GetMenuManager()->GetLoadingMenu()->loading = true;
			selectWorld = false;
		}
		break;
	case 1:
		Game::GetMenuManager()->GetOptionMenu()->SetEscapeToMainMenu(true);
		Game::GetMenuManager()->ResetActiveOption(Game::GetMenuManager()->GameOption);
		Game::GetMenuManager()->SetView(Game::GetMenuManager()->GameOption);
		//......
		break;
	case 2:
		//......
		break;
	}
}

void MainMenu::Escape()
{
	selectWorld = false;
}
