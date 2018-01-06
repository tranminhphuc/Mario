#include "LoadingMenu.h"
#include "Windows.h"
#include "Game.h"

LoadingMenu::LoadingMenu()
{
	time = 0;
	loading = true;
}

LoadingMenu::~LoadingMenu()
{
}

void LoadingMenu::Update(unsigned int Loadingtime)
{
	if (Loadingtime > time + 2500 + (loading ? 0 : 2750))
	{
		if (loading)
		{
			
		}
		else
		{
			Window::getMap()->ResetGameData();
		}
	}
	else
	{

	}
	Window::getMap()->UpdateBlock(time);
}

void LoadingMenu::Draw(sf::RenderWindow & window)
{
	Window::getMap()->DrawGameLayout(window);
	Game::GetText()->Draw(window, "WORLD", 320, 144);
}
