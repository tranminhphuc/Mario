#include "MenuManager.h"
#include "Windows.h"

MenuManager::MenuManager()
{
	currentGameState = MenuGame;

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

void MenuManager::Update()
{
	switch (currentGameState)
	{
	case MenuGame:
		Window::GetMap()->UpdateBlock();
		break;
	case GameLoading:
		loadingMenu->Update();
		break;
	case GamePlay:
		Window::GetMap()->Update();
		//Window::GetMap()->UpdateMinionsCollision();
		break;
	case GameOption:
		optionMenu->Update();
		break;
	case Pause:
		pauseMenu->Update();
		break;
	}
}

void MenuManager::Draw(sf::RenderWindow& window)
{
	switch (currentGameState)
	{
	case MenuGame:
		Window::GetMap()->DrawMap(window);
		mainMenu->Draw(window);
		break;
	case GameLoading:
		loadingMenu->Draw(window);
		break;
	case GamePlay:
		Window::GetMap()->Draw(window);
		break;
	case GameOption:
		Window::GetMap()->DrawMap(window);
		Window::GetMap()->DrawMinion(window);
		Window::GetMap()->DrawGameLayout(window);
		optionMenu->Draw(window);
		break;
	case Pause:
		Window::GetMap()->DrawMap(window);
		Window::GetMap()->DrawMinion(window);
		Window::GetMap()->DrawGameLayout(window);
		pauseMenu->Draw(window);
		break;
	}
}

void MenuManager::SetBackGroundColor(sf::RenderWindow & window)
{
	switch (currentGameState)
	{
	case MenuGame:
		Window::GetMap()->SetBackGroundColor(window);
		break;
	case GameLoading:
		Window::GetMap()->SetBackGroundColor(window, 0, 0, 0, 255);
		break;
	case GamePlay:
		Window::GetMap()->SetBackGroundColor(window);
		break;
	}
}

void MenuManager::Enter()
{
	switch (currentGameState)
	{
	case MenuGame:
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
	default:
		break;
	}
}

void MenuManager::Escape()
{
	switch (currentGameState)
	{
	case MenuGame:
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
	default:
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
	case MenuGame:
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
	case MenuGame:
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

int MenuManager::GetView()
{
	return currentGameState;
}

void MenuManager::SetView(GameState ID)
{
	currentGameState = ID;
}

LoadingMenu* MenuManager::GetLoadingMenu()
{
	return loadingMenu;
}

OptionMenu* MenuManager::GetOptionMenu()
{
	return optionMenu;
}
