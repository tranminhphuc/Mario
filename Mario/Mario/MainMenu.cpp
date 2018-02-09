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
	changeLevelFrom1To8 = changeLevelFrom1To4 = 0;

	selectWorldLabel.setSize(sf::Vector2f(122, 280));
	selectWorldLabel.setPosition(306, 72);
}

MainMenu::~MainMenu()
{
}

void MainMenu::Update()
{
	Menu::Update();
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	Menu::Draw(window);

	if (selectWorld)
	{
		/*selectWorldLabel.setFillColor(sf::Color(4, 4, 4, 255));
		selectWorldLabel.setSize(sf::Vector2f(selectWorldLabel.getSize().x + 1, selectWorldLabel.getSize().y + 1));
		selectWorldLabel.move(-2, -2);
		selectWorldLabel.setFillColor(sf::Color(255, 255, 255, 255));
		//selectWorldLabel.setSize(sf::Vector2f(selectWorldLabel.getSize().x - 1, selectWorldLabel.getSize().y - 1));
		//selectWorldLabel.move(2, 2);*/

		Game::GetText()->Draw(window, "SELECT WORLD", selectWorldLabel.getPosition().x + selectWorldLabel.getSize().x / 2 - Game::GetText()->GetTextWidth("SELECT WORLD)") / 2, selectWorldLabel.getPosition().y, 255, 255, 255);

		for (int i = 0, extraX = 0; i < 8; i++)
		{
			if (i == changeLevelFrom1To8)
			{
				Game::GetText()->Draw(window, std::to_string(i + 1) + "-" + std::to_string(changeLevelFrom1To4 + 1), selectWorldLabel.getPosition().x + 16 * (i + 1) + 16 * i + extraX, selectWorldLabel.getPosition().y + 16 + 24, 255, 255, 255);
				extraX = 32;
			}
			else
			{
				Game::GetText()->Draw(window, std::to_string(i + 1), selectWorldLabel.getPosition().x + 16 * (i + 1) + 16 * i + extraX, selectWorldLabel.getPosition().y + 16 + 24, 90, 90, 90);
			}
		}
	}
}

void MainMenu::UpdateActiveButton(int number)
{
	switch (number)
	{
	case Window::Up: case Window::Down:
		if (!selectWorld)
		{
			Menu::UpdateActiveButton(number);
		}
		else
		{
			switch (number)
			{
			case Window::Up:
				if (changeLevelFrom1To4 < 1)
					changeLevelFrom1To4 = 3;
				else
					changeLevelFrom1To4--;
				break;
			case Window::Down:
				if (changeLevelFrom1To4 > 2)
					changeLevelFrom1To4 = 0;
				else
					changeLevelFrom1To4++;
				break;
			}
		}
		break;
	case Window::Right:
		if (selectWorld)
		{
			if (changeLevelFrom1To8 < 7)
				changeLevelFrom1To8++;
			else
				changeLevelFrom1To8 = 0;
		}
		break;
	case Window::Left:
		if (selectWorld)
		{
			if (changeLevelFrom1To8 > 0)
				changeLevelFrom1To8--;
			else
				changeLevelFrom1To8 = 7;
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
			Window::GetMap()->SetLevel(changeLevelFrom1To8 * 4 + changeLevelFrom1To4);
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
