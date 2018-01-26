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
					Window::GetMap()->SetY(Window::GetMap()->GetPlayer()->GetY() - speed);
					oldLength[step] -= speed;
					break;
				case Bot:
					Window::GetMap()->SetY(Window::GetMap()->GetPlayer()->GetY() + speed);
					oldLength[step] -= speed;
					break;
				case Left:
					Window::GetMap()->SetX(Window::GetMap()->GetPlayer()->GetX() - speed);
					oldLength[step] -= speed;
					break;
				case Right:
					Window::GetMap()->SetX(Window::GetMap()->GetPlayer()->GetX() + speed);
					oldLength[step] -= speed;
					break;
				}
			}
			else
			{
				if (!endGame)
				{

				}
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
}

void Event::ResetData()
{

}
