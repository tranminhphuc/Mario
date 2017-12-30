#include "OptionMenu.h"

OptionMenu::OptionMenu()
{
	rect.setPosition(58, 48);
	rect.setSize(sf::Vector2f(403, 324));

	setKeyRect.setPosition(75, 284);
	setKeyRect.setSize(sf::Vector2f(369, 71));

	volumeChange.setPosition(185, 65);
	volumeChange.setSize(sf::Vector2f(16, 200));

	volume.setPosition(185, 65);
	volume.setSize(sf::Vector2f(16, 100));

	menuOption.push_back(new MenuOption("VOLUME", 73, 65));
	menuOption.push_back(new MenuOption("LEFT", 73, 89));
	menuOption.push_back(new MenuOption("DOWN", 73, 113));
	menuOption.push_back(new MenuOption("RIGHT", 73, 137));
	menuOption.push_back(new MenuOption("JUMP", 73, 161));
	menuOption.push_back(new MenuOption("RUN", 73, 185));
	menuOption.push_back(new MenuOption("MAIN MENU", 73, 257));

	numberOfMenuOption = menuOption.size();
	setKey = resetKey = false;
	escapeToMainMenu = true;
}

OptionMenu::~OptionMenu()
{
}

void OptionMenu::Update()
{
	if (resetKey)
	{
		setKey = false;
		resetKey = false;
	}
}

void OptionMenu::Draw(sf::RenderWindow & window)
{
}

void OptionMenu::Enter()
{
	switch (activeMenuOption)
	{
	case 0:
		break;
	case 1 : case 2 : case 3 : case 4: case 5:
		setKey = true;
		break;
	case 6:
		break;
	default:
		break;
	}
}

void OptionMenu::Escape()
{
	if (setKey)
	{
		resetKey = true;
	}
	else
	{
		if (escapeToMainMenu)
		{

		}
	}
}

void OptionMenu::SetKey(int keyID)
{
}

void OptionMenu::UpdateActiveButton(int id)
{
}
