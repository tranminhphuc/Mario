#include "Beetle.h"
#include "Windows.h"

Beetle::Beetle(int xMinion, int yMinion, int id, bool moveDirection)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;
	this->minionState = 0;
	this->id = Window::GetMap()->GetMapType() == Window::GetMap()->BanNgay ? 53 : Window::GetMap()->GetMapType() == Window::GetMap()->LongDat ? 55 : 57;
	this->moveDirection = moveDirection;
	this->moveSpeed = 1;
}

Beetle::~Beetle()
{
}

void Beetle::Update()
{
	if (minionState == -2)
		MinionDeathAnimation();
	else
		MoveX();
}

void Beetle::Draw(sf::RenderWindow & window, Texture * texture)
{
	if (minionState != -2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion));
}

void Beetle::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect())
	{
		SetMinionState(-2);
	}
	else if (top)
	{
		if (minionState == 0)
		{
			minionState = 1;
			id++;

			Window::GetMap()->GetPlayer()->ResetJump();
			Window::GetMap()->GetPlayer()->StartJump(1);
			Window::GetMap()->GetPlayer()->SetY(Window::GetMap()->GetPlayer()->GetY() - 4);

			moveSpeed = 0;
		}
		else
		{
			if (moveSpeed > 0)
			{
				moveSpeed = 0;
			}
			else
			{
				if ((xMinion + width) / 2 < Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2)
					moveDirection = true;
				else
					moveDirection = false;

				moveSpeed = 6;
			}

			Window::GetMap()->GetPlayer()->SetY(Window::GetMap()->GetPlayer()->GetY() - 4);
			Window::GetMap()->GetPlayer()->ResetJump();
			Window::GetMap()->GetPlayer()->StartJump(1);
		}
	}
	else
	{
		if (minionState == 1)
		{
			if (moveSpeed == 0)
			{
				moveDirection = (xMinion + width / 2 < Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2);

				if (moveDirection)
					xMinion -= Window::GetMap()->GetPlayer()->GetMoveSpeed() + 1;
				else
					xMinion += Window::GetMap()->GetPlayer()->GetMoveSpeed() + 1;

				moveSpeed = 6;
			}
			else
			{
				//Window::GetMap()->PlayerDeath();
			}
		}
	}
}

void Beetle::CollisionEffect()
{
	if (minionState == 0)
		moveDirection = !moveDirection;
}

void Beetle::SetMinionState(int minionState)
{
	if (minionState != -2 || Window::GetMap()->GetPlayer()->GetStarEffect())
		Minion::SetMinionState(minionState);
	else
		moveDirection = !moveDirection;
}
