#include "MenuManager.h"
#include "Windows.h"
#include "Game.h"

MenuManager::MenuManager()
{
	mainMenu = new MainMenu();
	loadingMenu = new LoadingMenu();
	optionMenu = new OptionMenu();
	pauseMenu = new PauseMenu();
}

MenuManager::~MenuManager()
{
	delete mainMenu;
	delete loadingMenu;
	delete optionMenu;
	delete pauseMenu;
}

void MenuManager::Update(unsigned int time)
{
	switch (currentGameState)
	{
	case MainMenuGame:
		mainMenu->Update();
		Window::getMap()->UpdateBlock(time);
		break;
	case GameLoading:
		loadingMenu->Update(time);
		break;
	case GamePlay:
		Window::getMap()->Update();
		break;
	case GameOption:
		optionMenu->Update();
		break;
	case Pause:
		pauseMenu->Update();
		break;
	}
}

void MenuManager::Draw(sf::RenderWindow & window)
{
}

void MenuManager::SetBackGroundColor(sf::RenderWindow & window)
{
	switch (currentGameState)
	{
	case MainMenuGame:
		Window::getMap()->SetBackGroundColor(window);
		break;
	case GameLoading:
		Window::getMap()->SetBackGroundColor(window, 0, 0, 0, 255);
		break;
	case GamePlay:
		Window::getMap()->SetBackGroundColor(window);
		break;
	}
}

void MenuManager::Enter()
{
	switch (currentGameState)
	{
	case MainMenuGame:
		mainMenu->Enter();
		break;
	case GamePlay:
		break;
	case GameOption:
		optionMenu->Enter();
		break;
	case Pause:
		pauseMenu->Enter();
		break;
	}
}

void MenuManager::Escape()
{
	switch (currentGameState)
	{
	case MainMenuGame:
		mainMenu->Escape();
		break;
	case GamePlay:
		break;
	case GameOption:
		optionMenu->Escape();
		break;
	case Pause:
		pauseMenu->Escape();
		break;
	}
}

void MenuManager::SetKey(int id)
{
	switch (currentGameState)
	{
	case GameOption:
		optionMenu->SetKey(id);
		break;
	default:
		break;
	}
}

void MenuManager::keyPressed(int id)
{
	switch (currentGameState)
	{
	case MainMenuGame:
		mainMenu->UpdateActiveButton(id);
		break;
	case GameOption:
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
	case MainMenuGame:
		mainMenu->activeMenuOption = 0;
		break;
	case GameOption:
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
	return currentGameState;
}

void MenuManager::SetState(GameState ID)
{
	currentGameState = ID;
}
