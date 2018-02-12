#include "OptionMenu.h"
#include "Windows.h"
#include "Game.h"

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

	numberOfMenuOption = (int)menuOption.size();
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
	rect.setFillColor(sf::Color(4, 4, 4, 255));
	rect.setSize(sf::Vector2f(rect.getSize().x + 1, rect.getSize().y + 1));
	rect.move(-2, -2);
	rect.setFillColor(sf::Color(255, 255, 255, 255));
	rect.setSize(sf::Vector2f(rect.getSize().x - 1, rect.getSize().y - 1));
	rect.move(2, 2);

	for (int i = 0; i < menuOption.size(); i++)
	{
		if(i == activeMenuOption)
			Game::GetText()->Draw(window, menuOption[i]->GetText(), menuOption[i]->GetX(), menuOption[i]->GetY(), 255, 255, 255);
		else
			Game::GetText()->Draw(window, menuOption[i]->GetText(), menuOption[i]->GetX(), menuOption[i]->GetY(), 90, 90, 90);
	}

	volume.setFillColor(sf::Color(4, 4, 4, 255));
	volumeChange.setFillColor(sf::Color(activeMenuOption == 0 ? 150 : 90, activeMenuOption == 0 ? 150 : 90, activeMenuOption == 0 ? 150 : 90, 255));

	if (activeMenuOption == 0)
		volumeChange.setFillColor(sf::Color(255, 255, 255, 255));
	else
		volumeChange.setFillColor(sf::Color(160, 160, 160, 255));

	Game::GetText()->Draw(window, Game::GetKeyString(Game::keyA), 185, 89, activeMenuOption == 1 ? 255 : 90, activeMenuOption == 1 ? 255 : 90, activeMenuOption == 1 ? 255 : 90);
	Game::GetText()->Draw(window, Game::GetKeyString(Game::keyS), 185, 113, activeMenuOption == 2 ? 255 : 90, activeMenuOption == 2 ? 255 : 90, activeMenuOption == 2 ? 255 : 90);
	Game::GetText()->Draw(window, Game::GetKeyString(Game::keyD), 185, 137, activeMenuOption == 3 ? 255 : 90, activeMenuOption == 3 ? 255 : 90, activeMenuOption == 3 ? 255 : 90);
	Game::GetText()->Draw(window, Game::GetKeyString(Game::keySpace), 185, 161, activeMenuOption == 4 ? 255 : 90, activeMenuOption == 4 ? 255 : 90, activeMenuOption == 4 ? 255 : 90);
	Game::GetText()->Draw(window, Game::GetKeyString(Game::keyShift), 185, 185, activeMenuOption == 5 ? 255 : 90, activeMenuOption == 5 ? 255 : 90, activeMenuOption == 5 ? 255 : 90);

	if (setKey)
	{
		setKeyRect.setFillColor(sf::Color(20, 20, 20, 245));
		setKeyRect.setSize(sf::Vector2f(setKeyRect.getSize().x + 1, setKeyRect.getSize().y + 1));
		setKeyRect.move(-2, -2);
		setKeyRect.setFillColor(sf::Color(255, 255, 255, 245));
		setKeyRect.setSize(sf::Vector2f(setKeyRect.getSize().x - 1, setKeyRect.getSize().y - 1));
		setKeyRect.move(2, 2);

		Game::GetText()->Draw(window, "PRESS KEY FOR " + menuOption[activeMenuOption]->GetText(), 92, setKeyRect.getPosition().y, 255, 255, 255);
		Game::GetText()->Draw(window, "PRESS ESC TO CALCEL", 92, setKeyRect.getPosition().y + 40, 255, 255, 255);
	}
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
		Window::GetMap()->ResetGameData();
		Game::GetMenuManager()->SetView(Game::GetMenuManager()->MenuGame);
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
			Window::GetMap()->ResetGameData();
			Game::GetMenuManager()->SetView(Game::GetMenuManager()->MenuGame);
		}
		else
		{
			Game::GetMenuManager()->SetView(Game::GetMenuManager()->Pause);
		}
	}
}

void OptionMenu::SetKey(int keyID)
{
	if (setKey && keyID != sf::Keyboard::Return && keyID != sf::Keyboard::Escape)
	{
		switch (activeMenuOption)
		{
		case 1:
			Game::keyA = keyID;
			if (Game::keyD == keyID) Game::keyD = 0;
			if (Game::keyS == keyID) Game::keyS = 0;
			if (Game::keySpace == keyID) Game::keySpace = 0;
			if (Game::keyShift == keyID) Game::keyShift = 0;
			break;
		case 2:
			Game::keyD = keyID;
			if (Game::keyA == keyID) Game::keyA = 0;
			if (Game::keyS == keyID) Game::keyS = 0;
			if (Game::keySpace == keyID) Game::keySpace = 0;
			if (Game::keyShift == keyID) Game::keyShift = 0;
			break;
		case 3:
			Game::keyS = keyID;
			if (Game::keyA == keyID) Game::keyA = 0;
			if (Game::keyD == keyID) Game::keyD = 0;
			if (Game::keySpace == keyID) Game::keySpace = 0;
			if (Game::keyShift == keyID) Game::keyShift = 0;
			break;
		case 4:
			Game::keySpace = keyID;
			if (Game::keyA == keyID) Game::keyA = 0;
			if (Game::keyD == keyID) Game::keyD = 0;
			if (Game::keyS == keyID) Game::keyS = 0;
			if (Game::keyShift == keyID) Game::keyShift = 0;
			break;
		case 5:
			Game::keyShift = keyID;
			if (Game::keyA == keyID) Game::keyA = 0;
			if (Game::keyD == keyID) Game::keyD = 0;
			if (Game::keyS == keyID) Game::keyS = 0;
			if (Game::keySpace == keyID) Game::keySpace = 0;
			break;
		}
		resetKey = true;
	}
	else if (keyID == sf::Keyboard::Escape)
	{
		resetKey = true;
	}
}

void OptionMenu::UpdateActiveButton(int id)
{
	if (activeMenuOption == 0 && (id == Window::Left || id == Window::Right))
	{
		switch (id)
		{
		case Window::Left:
			break;
		case Window::Right:
			break;
		}

		UpdateVolumeRect();
	}

	if (!setKey)
		Menu::UpdateActiveButton(id);
}

void OptionMenu::UpdateVolumeRect()
{

}

void OptionMenu::SetEscapeToMainMenu(bool escapeToMainMenu)
{
	this->escapeToMainMenu = escapeToMainMenu;
}
