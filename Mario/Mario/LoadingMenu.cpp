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
			Window::GetMenuManager()->SetView(Window::GetMenuManager()->GamePlay);
		}
		else
		{
			Window::GetMap()->ResetGameData();
			Window::GetMenuManager()->SetView(Window::GetMenuManager()->MenuGame);
		}
	}
	else
	{

	}

	Window::GetMap()->UpdateBlock();
}

void LoadingMenu::Draw(sf::RenderWindow & window)
{
	Window::GetMap()->SetBackGroundColor(window);
	if (loading)
	{
		Window::GetMap()->DrawGameLayout(window);
		Window::GetText()->Draw(window, "WORLD", 320, 144);
		Window::GetText()->Draw(window, Window::GetMap()->GetLevelName(), 416, 144);
		Window::GetText()->Draw(window, "y", 384, 208);
	}
	else
	{
		Window::GetMap()->DrawGameLayout(window);
		Window::GetText()->DrawCenterX(window, "GAME OVER", 240);
	}
}

void LoadingMenu::UpdateTime()
{
	time = Window::GetTime();
}
