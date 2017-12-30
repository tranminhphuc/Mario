#include "MenuManager.h"
#include "Windows.h"


MenuManager::MenuManager()
{
}


MenuManager::~MenuManager()
{
}

void MenuManager::Update()
{
}

void MenuManager::Draw(sf::RenderWindow & window)
{
}

void MenuManager::SetBackGroundColor(sf::RenderWindow & window)
{
	switch (currentgameState)
	{
	case MainMenu:
		Window::getMap()->SetBackGroundColor(window);
		break;
	case Loading:
		Window::getMap()->SetBackGroundColor(window, 0, 0, 0, 255);
		break;
	case Game:
		Window::getMap()->SetBackGroundColor(window);
		break;
	}
}

void MenuManager::Enter()
{
	switch (currentgameState)
	{
	case MainMenu:
		mainMenu->Enter();
		break;
	case Game:
		break;
	case Option:
		optionMenu->Enter();
		break;
	case Pause:
		pauseMenu->Enter();
		break;
	}
}

void MenuManager::Escape()
{
	switch (currentgameState)
	{
	case MainMenu:
		mainMenu->Escape();
		break;
	case Game:
		break;
	case Option:
		optionMenu->Escape();
		break;
	case Pause:
		pauseMenu->Escape();
		break;
	}
}

void MenuManager::SetKey(int id)
{
	switch (currentgameState)
	{
	case Option:
		optionMenu->SetKey(id);
		break;
	default:
		break;
	}
}

void MenuManager::keyPressed(int id)
{
	switch (currentgameState)
	{
	case MainMenu:
		mainMenu->UpdateActiveButton(id);
		break;
	case Option:
		optionMenu->UpdateActiveButton(id);
		break;
	case Pause:
		pauseMenu->UpdateActiveButton(id);
		break;
	default:
		break;
	}
}

void MenuManager::ResetActiveOption(GameState id)
{
	switch (id)
	{
	case MainMenu:
		mainMenu->activeMenuOption = 0;
		break;
	case Option:
		optionMenu->activeMenuOption = 0;
		break;
	case Pause:
		pauseMenu->activeMenuOption = 0;
		break;
	default:
		break;
	}
}

int MenuManager::GetState()
{
	return currentgameState;
}

void MenuManager::SetState(GameState ID)
{
	currentgameState = ID;
}
