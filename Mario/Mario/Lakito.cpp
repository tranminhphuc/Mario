#include "Lakito.h"
#include "Windows.h"

Lakito::Lakito(int xMinion, int yMinion, int maxX)
{
	srand((unsigned int)time(NULL));

	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;
	this->maxX = maxX;

	this->followPlayer = false;
	this->end = false;

	this->id = 50;
	this->width = 32;
	this->height = 26;

	this->collisionOnlyWithPlayer = true;

	this->moveDirection = true;
	this->minionSpawned = true;
}

Lakito::~Lakito()
{
}

void Lakito::Update()
{
	if (minionState == -2)
	{
		MinionDeathAnimation();
	}
	else
	{
		if (xMinion > maxX)
			end = true;

		if (end)
		{
			xMinion = -1;

			if (xMinion < -width)
				minionState = -1;

			return;
		}

		if (xMinion < -Window::GetMap()->GetX() - 64)
			xMinion = -Window::GetMap()->GetX() - 32;

		if (xMinion <= Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2 + 32 * Window::GetMap()->GetPlayer()->GetMoveSpeed() && Window::GetMap()->GetPlayer()->getMove())
		{
			moveSpeed = Window::GetMap()->GetPlayer()->GetMoveSpeed() + (xMinion < Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2 + 32 * Window::GetMap()->GetPlayer()->GetMoveSpeed());
			xMinion += moveSpeed;
			followPlayer = true;
			moveDirection = true;
		}
		else
		{
			if (followPlayer)
			{
				if (moveSpeed > 0)
				{
					xMinion += moveSpeed;
					moveSpeed--;
				}
				else
				{
					followPlayer = false;
				}
			}
			else
			{
				if (!moveDirection)
				{
					xMinion = -1;

					if (xMinion < Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2 - 128)
						moveDirection = true;
				}
				else
				{
					xMinion += 1;

					if (xMinion > Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2 + 128)
						moveDirection = false;
				}
			}
		}
	}
}

void Lakito::Draw(sf::RenderWindow & window, Texture * texture)
{
	if(minionState != -2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion - 16));
}

void Lakito::MinionPhysics() { };

void Lakito::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect() || top)
		SetMinionState(-2);
	else if (!end)
		Window::GetMap()->PlayerDeath();
}
