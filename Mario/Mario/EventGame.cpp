#include "EventGame.h"
#include "Windows.h"

Event::Event()
{
	time = 0;
	delay = 0;
	endGame = false;
}

Event::~Event()
{
}

void Event::Normal()
{
	if (state)
	{
		if (oldDir.size() > step)
		{
			if (oldLength[step] > 0)
			{
				switch (oldDir[step])
				{
				case Top:
					Window::GetMap()->GetPlayer()->SetY(Window::GetMap()->GetPlayer()->GetY() - speed);
					oldLength[step] -= speed;
					break;
				case Bot:
					Window::GetMap()->GetPlayer()->SetY(Window::GetMap()->GetPlayer()->GetY() + speed);
					oldLength[step] -= speed;
					break;
				case Left:
					Window::GetMap()->GetPlayer()->SetX(Window::GetMap()->GetPlayer()->GetX() - speed);
					oldLength[step] -= speed;
					break;
				case Right:
					Window::GetMap()->GetPlayer()->SetX(Window::GetMap()->GetPlayer()->GetX() + speed);
					oldLength[step] -= speed;
					break;
				case ScoreEnd:
					if (Window::GetMap()->GetMapTime() > 0)
					{
						Window::GetMap()->SetMapTime(Window::GetMap()->GetMapTime() - 1);
						Window::GetMap()->GetPlayer()->SetScore(Window::GetMap()->GetPlayer()->GetScore() + 50);
					}
					else
					{
						oldLength[step] = 0;
					}

					break;
				case LoadingMenu:
					oldLength[step] -= 1;

					if (oldLength[step] < 2)
					{
						inEvent = false;
						Window::GetMap()->GetPlayer()->StopMove();

						Window::GetMenuManager()->GetLoadingMenu()->loading = true;
						Window::GetMenuManager()->GetLoadingMenu()->UpdateTime();
						Window::GetMenuManager()->SetView(Window::GetMenuManager()->GameLoading);
					}

					break;
				case GameOver:
					oldLength[step] -= 1;

					if (oldLength[step] < 2)
					{
						inEvent = false;
						Window::GetMap()->GetPlayer()->StopMove();

						Window::GetMenuManager()->GetLoadingMenu()->loading = false;
						Window::GetMenuManager()->GetLoadingMenu()->UpdateTime();
						Window::GetMenuManager()->SetView(Window::GetMenuManager()->GameLoading);
					}

					break;
				case BossEnd1:
					for (int i = Window::GetMap()->GetWidth() - 1; i > 0; i--)
					{
						if (Window::GetMap()->GetTile(i, 6)->GetID() == 115)
						{
							Window::GetMap()->GetTile(i, 6)->SetID(0);
							break;
						}
					}

					oldLength[step] = 0;
					break;
				case BossEnd2:
					for (int i = Window::GetMap()->GetWidth() - 1; i > 0; i--)
					{
						if (Window::GetMap()->GetTile(i, 5)->GetID() == 111)
						{
							Window::GetMap()->GetTile(i, 5)->SetID(0);
							break;
						}
					}

					for (int i = Window::GetMap()->GetWidth() - 1; i > 0; i--)
					{
						if (Window::GetMap()->GetTile(i, 4)->GetID() == 110)
						{
							Window::GetMap()->GetTile(i, 4)->SetID(0);
							break;
						}
					}

					oldLength[step] = 0;
					break;
				case BossEnd3:
					for (int i = Window::GetMap()->GetWidth() - 1; i > 0; i--)
					{
						if (Window::GetMap()->GetTile(i, 4)->GetID() == 110)
						{
							Window::GetMap()->GetTile(i, 4)->SetID(0);
							break;
						}
					}

					oldLength[step] = 0;
					break;
				case BossEnd4:
					oldLength[step] = 0;
					break;
				case BossEndText1:
					oldLength[step] = 0;
					break;
				case BossEndText2:
					oldLength[step] = 0;
					break;
				}
			}
			else
			{
				step++;
				time = Window::GetTime();
			}
		}
		else
		{
			if (!endGame)
			{
				if (Window::GetTime() >= time + delay)
				{
					state = false;
					step = 0;
					NewLevel();
					Window::GetMap()->GetPlayer()->StopMove();

					if (inEvent)
					{
						Window::GetMenuManager()->GetLoadingMenu()->UpdateTime();
						Window::GetMenuManager()->GetLoadingMenu()->loading = true;
						Window::GetMenuManager()->SetView(Window::GetMenuManager()->GameLoading);
					}

					Window::keySpace = false;
				}
			}
			else
			{
				Window::GetMap()->ResetGameData();
				Window::GetMenuManager()->SetView(Window::GetMenuManager()->MenuGame);
				Window::GetMap()->GetPlayer()->StopMove();
				Window::keySpace = false;
				inEvent = false;
				endGame = false;
				step = 0;
			}
		}
	}
	else
	{
		if (newDir.size() > step)
		{
			if (newDir[step] > 0)
			{
				switch (newDir[step])
				{
				case Top:
					Window::GetMap()->GetPlayer()->SetY(Window::GetMap()->GetPlayer()->GetY() - speed);
					newLenght[step] -= speed;
					break;
				case Bot:
					Window::GetMap()->GetPlayer()->SetY(Window::GetMap()->GetPlayer()->GetY() + speed);
					newLenght[step] -= speed;
					break;
				case Left:
					Window::GetMap()->GetPlayer()->SetX(Window::GetMap()->GetPlayer()->GetY() - speed);
					newLenght[step] -= speed;
					break;
				case Right:
					Window::GetMap()->GetPlayer()->SetX(Window::GetMap()->GetPlayer()->GetY() + speed);
					newLenght[step] -= speed;
					break;
				}
			}
			else
			{
				step++;
			}
		}
		else
		{
			Window::GetMap()->GetPlayer()->StopMove();
			Window::space = false;
			Window::ResetKeys();
			inEvent = false;
		}
	}
}

void Event::End()
{

}

void Event::NewLevel()
{
	Window::GetMap()->SetX((float)newMapX);
	Window::GetMap()->GetPlayer()->SetX(newPlayerX);
	Window::GetMap()->GetPlayer()->SetY(newPlayerY);
	Window::GetMap()->SetMoveMap(newMoveMap);

	if (true)
	{
		Window::GetMenuManager()->GetLoadingMenu()->UpdateTime();
		Window::GetMenuManager()->GetLoadingMenu()->loading = true;
		Window::GetMenuManager()->SetView(Window::GetMenuManager()->GameLoading);
		Window::GetMap()->GetPlayer()->SetCoin(0);
	}

	Window::GetMap()->SetLevel(newLevel);

	if (newUnderWater)
		Window::GetMap()->GetPlayer()->ResetMove();

	Window::GetMap()->SetUnderWater(newUnderWater);
}

void Event::ResetData()
{
	newDir.clear();
	newLenght.clear();
	oldDir.clear();
	oldLength.clear();

	eventType = normal;

	step = 0;
	state = true;
	inEvent = false;
	endGame = false;
	newUnderWater = false;
}
