#include "Squid.h"
#include "Windows.h"
#include "Game.h"

Squid::Squid(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;

	width = 32;
	minionState = 0;
	moveDirection = false;
	moveSpeed = 2;
}

Squid::~Squid()
{
}

void Squid::Update()
{
	if (Window::GetMap()->GetUnderWater())
	{
		if (moveXDistance <= 0)
		{
			if (moveYDistance > 0)
			{
				yMinion += 1;
				moveYDistance -= 1;

				if (moveYDistance == 0)
					ChangeID();
			}
			else
			{
				if (yMinion + 52 > Window::GetMap()->GetPlayer()->GetY())
				{
					moveDirection = Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2 > xMinion;
					moveXDistance = 96 * rand() % 32;
					ChangeID();
				}
				else
				{
					yMinion += 1;
				}
			}
		}
		else
		{
			if (moveXDistance == 64)
				ChangeID();

			xMinion += moveDirection ? 2 : -2;

			if (yMinion > Game::gameHeight - 12 * 32 - 4)
				yMinion -= 2;

			moveXDistance -= 2;

			if (moveXDistance <= 0)
			{
				ChangeID();
				moveYDistance = 32;
			}
		}
	}
}

void Squid::Draw(sf::RenderWindow & window, Texture * texture)
{
	texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion));
}

void Squid::CollisionWithPlayer(bool top)
{
	Window::GetMap()->PlayerDeath();
}

void Squid::ChangeID()
{
	switch (id)
	{
	case 28:
		id = 29;
		height = 28;
		break;
	default:
		id = 28;
		height = 28;
		break;
	}
}
