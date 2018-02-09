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

string Game::GetKeyString(int keyID)
{
	if (keyID >= 97 && keyID <= 122)
		return string(1, '0' + (keyID - 32) - 48);

	if(keyID >= 48 && keyID <= 57)
		return string(1, '0' + (keyID - 32) - 48);

	switch (keyID)
	{
	case sf::Keyboard::Escape:
		return "ESCAPE";
	case sf::Keyboard::Space:
		return "SPACE";
	case sf::Keyboard::LShift:
		return "LSHIFT";
	case sf::Keyboard::RShift:
		return "RSHIFT";
	case sf::Keyboard::Up:
		return "UP";
	case sf::Keyboard::Down:
		return "DOWN";
	case sf::Keyboard::Left:
		return "LEFT";
	case sf::Keyboard::Right:
		return "RIGHT";
	case sf::Keyboard::LControl:
		return "LCONTROl";
	case sf::Keyboard::RControl:
		return "RCONTROL";
	}

	return "NONE";
}


