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
			Game::GetMenuManager()->SetView(Game::GetMenuManager()->GamePlay);
		}
		else
		{
			Window::GetMap()->ResetGameData();
			Game::GetMenuManager()->SetView(Game::GetMenuManager()->MenuGame);
		}
	}
	else
	{

	}
	Window::GetMap()->UpdateBlock();
}

void LoadingMenu::Draw(sf::RenderWindow & window)
{
	if (loading)
	{
		Window::GetMap()->DrawGameLayout(window);
		Game::GetText()->Draw(window, "WORLD", 320, 144);
		Game::GetText()->Draw(window, Window::GetMap()->GetLevelName(), 416, 144);
		Game::GetText()->Draw(window, "y", 384, 208);
		Game::GetText()->DrawCenterX(window, "REMEMBER THAT YOU CAN RUN WITH" + Game::GetKeyString(Game::keyShift), 400);
	}
	else
	{
		Window::GetMap()->DrawGameLayout(window);
		Game::GetText()->DrawCenterX(window, "GAME OVER", 240);
	}
}

void LoadingMenu::UpdateTime()
{
	time = Window::GetTime();
}
