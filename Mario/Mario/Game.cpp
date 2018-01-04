#include "Game.h"

int Game::gameWidth = 800;
int Game::gameHeight = 480;

int Game::keyA = 0;
int Game::keyD = 0;
int Game::keyS = 0;
int Game::keySpace = 0;
int Game::keyShift = 0;

Text* Game::text = new Text();
MenuManager* Game::menuManager = new MenuManager();

Game::Game()
{
}

Game::~Game()
{
}

Text* Game::GetText()
{
	return text;
}

MenuManager* Game::GetMenuManager()
{
	return menuManager;
}


