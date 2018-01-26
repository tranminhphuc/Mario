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

void LoadingMenu::Update()
{
	if (Window::GetTime() > time + 2500 + (loading ? 0 : 2750))
	{
		if (loading)
		{
			
		}
		else
		{
			Window::GetMap()->ResetGameData();
		}
	}
	else
	{

	}
	Window::GetMap()->UpdateBlock();
}

void LoadingMenu::Draw(sf::RenderWindow & window)
{
	Window::GetMap()->DrawGameLayout(window);
	Game::GetText()->Draw(window, "WORLD", 320, 144);
}

void LoadingMenu::UpdateTime()
{
	time = Window::GetTime();
}
