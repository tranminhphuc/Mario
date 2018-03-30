#include "Cheep.h"
#include "Windows.h"

Cheep::Cheep(int xMinion, int yMinion, int minionType, int moveSpeed, bool moveDirection)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;

	this->moveDirection = false;

	this->width = 30;
	this->height = 28;

	if (minionType == 0)
	{
		this->minionState = 1;
		this->moveSpeed = 2;
		this->id = 31;
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

	this->collisionOnlyWithPlayer = true;
}

Cheep::~Cheep() { }

void Cheep::Update()
{
	if (minionState == 0)
	{
		if (xMinion + width < 0)
			minionState = -1;
		else
			xMinion -= moveSpeed / 2;
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
				ChangeDistance(-8, 8);
			else if (jumpDistance > 9 * 32)
				ChangeDistance(-7.5f, 7.5f);
			else if (jumpDistance > 8 * 32)
				ChangeDistance(-7, 7);
			else if (jumpDistance > 6 * 32)
				ChangeDistance(-6.5f, 6.5f);
			else if (jumpDistance > 5 * 32)
				ChangeDistance(-5.5f, 5.5f);
			else if (jumpDistance > 4 * 32)
				ChangeDistance(-4.5f, 4.5f);
			else if (jumpDistance > 2 * 32)
				ChangeDistance(-3.5f, 3.5f);
			else if (jumpDistance > 0)
				ChangeDistance(-2.5f, 2.5f);
		}
		else
		{
			if (jumpDistance > 11 * 32)
				ChangeDistance(2.5f, 2.5f);
			else if (jumpDistance > 9 * 32)
				ChangeDistance(3.5f, 3.5f);
			else if (jumpDistance > 8 * 32)
				ChangeDistance(4.5f, 4.5f);
			else if (jumpDistance > 7 * 32)
				ChangeDistance(5.5f, 5.5f);
			else if (jumpDistance > 6 * 32)
				ChangeDistance(6.5f, 6.5f);
			else if (jumpDistance > 4 * 32)
				ChangeDistance(7, 7);
			else if (jumpDistance > 3 * 32)
				ChangeDistance(7.5f, 7.5f);
			else
				ChangeDistance(8, 8);

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

void Cheep::MinionPhysics() { };

void Cheep::CollisionWithPlayer(bool top)
{
	if (minionState > 1 && top)
	{
		SetMinionState(-2);
		moveYDir = false;
		jumpDistance = Window::gameHeight - yMinion;
	}
	else
	{
		Window::GetMap()->PlayerDeath();
	}
}

void Cheep::ChangeDistance(float y, float distance)
{
	yMinion += y;
	jumpDistance += distance;
}