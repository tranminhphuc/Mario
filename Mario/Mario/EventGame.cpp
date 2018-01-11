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
					Window::getMap()->SetY(Window::getMap()->GetPlayer()->GetY() - speed);
					oldLength[step] -= speed;
					break;
				case Bot:
					Window::getMap()->SetY(Window::getMap()->GetPlayer()->GetY() + speed);
					oldLength[step] -= speed;
					break;
				case Left:
					Window::getMap()->SetX(Window::getMap()->GetPlayer()->GetX() - speed);
					oldLength[step] -= speed;
					break;
				case Right:
					Window::getMap()->SetX(Window::getMap()->GetPlayer()->GetX() + speed);
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
					Window::getMap()->GetPlayer()->SetY(Window::getMap()->GetPlayer()->GetY() - speed);
					newLenght[step] -= speed;
					break;
				case Bot:
					Window::getMap()->GetPlayer()->SetY(Window::getMap()->GetPlayer()->GetY() + speed);
					newLenght[step] -= speed;
					break;
				case Left:
					Window::getMap()->GetPlayer()->SetX(Window::getMap()->GetPlayer()->GetY() - speed);
					newLenght[step] -= speed;
					break;
				case Right:
					Window::getMap()->GetPlayer()->SetX(Window::getMap()->GetPlayer()->GetY() + speed);
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
	Window::getMap()->SetX(newMapX);
	Window::getMap()->GetPlayer()->SetX(newPlayerX);
	Window::getMap()->GetPlayer()->SetY(newPlayerY);
	Window::getMap()->SetMoveMap(newMoveMap);
}

void Event::ResetData()
{

}
