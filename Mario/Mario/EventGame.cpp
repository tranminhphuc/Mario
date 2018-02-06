#include "EventGame.h"
#include "Windows.h"
#include "Game.h"

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
					//Window::GetMap()->GetPlayer()->StopMove();
					//......
					Game::keySpace = false;
				}
			}
			else
			{
				Window::GetMap()->ResetGameData();
				//......
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
			//......
		}
	}
}

void Event::End()
{

}

void Event::NewLevel()
{
	Window::GetMap()->SetX(newMapX);
	Window::GetMap()->GetPlayer()->SetX(newPlayerX);
	Window::GetMap()->GetPlayer()->SetY(newPlayerY);
	Window::GetMap()->SetMoveMap(newMoveMap);
	//......
	if (newUnderWater)
	{
		Window::GetMap()->GetPlayer()->ResetMove();
	}

	Window::GetMap()->SetUnderWater(newUnderWater);
}

void Event::ResetData()
{
	newDir.clear();
	newLenght.clear();
	oldDir.clear();
	oldLength.clear();

	step = 0;
	state = true;
	inEvent = false;
	endGame = false;
	newUnderWater = false;
}
