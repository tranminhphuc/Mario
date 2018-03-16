#include "Cheep.h"
#include "Windows.h"

Cheep::Cheep(int xMinion, int yMinion, int minionType, int moveSpeed, bool moveDirection)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;

	this->moveY = false;
	this->moveDirection = false;

	this->width = 30;
	this->height = 28;

	if (minionType == 1)
	{
		this->minionState = 1;
		this->moveSpeed = 2;
		this->id = 31;
	}
	else if(minionType == 0)
	{
		this->minionState = 0;
		this->moveSpeed = 1;
		this->id = 30;
	}
	else
	{
		this->minionState = minionType;
		this->moveSpeed = moveSpeed;
		this->id = 31;

		this->moveDirection = moveDirection;

		this->height = 20;

		this->jumpDistance = 11 * 32.0f + rand() % 80;
		moveYDir = true;
	}
}

Cheep::~Cheep()
{
}

void Cheep::Update(unsigned int time)
{
	if (minionState == 0 || minionState == 1)
	{
		if (xMinion + width < 0)
			minionState = -1;
		else
			xMinion -= moveSpeed / 2;

		if (moveY)
		{
			if (moveYDir)
			{
				if (jumpDistance > 0)
				{
					if (yMinion > Window::gameHeight - 12 * 32 + 8)
					{
						yMinion -= 0.25f;
					}

					jumpDistance--;
				}
				else
				{
					jumpDistance = 80 * 4.0f + (rand() % 32) * 4;
					moveYDir = !moveYDir;
				}
			}
			else
			{
				if (jumpDistance > 0)
				{
					yMinion += 0.25f;
					jumpDistance--;
				}
				else
				{
					jumpDistance = 80 * 4.0f + (rand() % 32) * 4;
					moveYDir = !moveYDir;
				}
			}
		}
		else
		{
			moveY = rand() % 218 == 0;

			if (moveY)
			{
				jumpDistance = (float)(rand() % 96);
				moveYDir = rand() % 2 == 0;
			}
		}
	}
	else
	{
		if (xMinion + width < 0)
			minionState = -1;
		else
			xMinion += moveDirection ? moveSpeed / 4.0f : -moveSpeed / 4.0f;

		if (moveYDir)
		{
			if (jumpDistance > 10 * 32)
			{
				yMinion -= 8;
				jumpDistance -= 8;
			}
			else if (jumpDistance > 9 * 32)
			{
				yMinion -= 7.5f;
				jumpDistance -= 7.5f;
			}
			else if (jumpDistance > 8 * 32)
			{
				yMinion -= 7;
				jumpDistance -= 7;
			}
			else if (jumpDistance > 6 * 32)
			{
				yMinion -= 6.5f;
				jumpDistance -= 6.5f;
			}
			else if (jumpDistance > 5 * 32)
			{
				yMinion -= 5.5f;
				jumpDistance -= 5.5f;
			}
			else if (jumpDistance > 4 * 32)
			{
				yMinion -= 4.5f;
				jumpDistance -= 4.5f;
			}
			else if (jumpDistance > 2 * 32)
			{
				yMinion -= 3.5f;
				jumpDistance -= 3.5f;
			}
			else if (jumpDistance > 0)
			{
				yMinion -= 2.5f;
				jumpDistance -= 2.5f;
			}
		}
		else
		{
			if (jumpDistance > 11 * 32)
			{
				yMinion += 2.5f;
				jumpDistance -= 2.5f;
			}
			else if (jumpDistance > 9 * 32)
			{
				yMinion += 3.5f;
				jumpDistance -= 3.5f;
			}
			else if (jumpDistance > 8 * 32)
			{
				yMinion += 4.5f;
				jumpDistance -= 4.5f;
			}
			else if (jumpDistance > 7 * 32)
			{
				yMinion += 5.5f;
				jumpDistance -= 5.5f;
			}
			else if (jumpDistance > 6 * 32)
			{
				yMinion += 6.5f;
				jumpDistance -= 6.5f;
			}
			else if (jumpDistance > 4 * 32)
			{
				yMinion += 7;
				jumpDistance -= 7;
			}
			else if (jumpDistance > 3 * 32)
			{
				yMinion += 7.5f;
				jumpDistance -= 7.5f;
			}
			else
			{
				yMinion += 8;
				jumpDistance -= 8;
			}

			if (yMinion > Window::gameHeight)
				minionState = -1;
		}
	}
}

void Cheep::Draw(sf::RenderWindow & window, Texture * texture)
{
	if (minionState != -2)
		texture->Draw(window, sf::Vector2f(xMinion + Window::GetMap()->GetX(), yMinion + 2));
}

void Cheep::CollisionWithPlayer(bool top)
{
}
