#include "Hammer.h"
#include "Windows.h"
#include "Game.h"

Hammer::Hammer(int xMinion, int yMinion)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;

	width = 24;
	height = 24;

	this->moveDirection = moveDirection;

	jumpState = NhayLen;
	jumpDistance = 48;
	currentJumpDistance = 0;
	moveSpeed = 0;

	minionState = 0;
	minionSpawned = false;
}

Hammer::~Hammer()
{
}

void Hammer::Update()
{
	if (minionState != -2)
	{
		moveSpeed++;

		if (moveSpeed > 35)
			xMinion += moveDirection ? 3 : -3;
		else if (moveSpeed > 15)
			xMinion += moveDirection ? 2.5f : -2.5f;
		else
			xMinion += moveDirection ? 2 : -2;
	}
	else
	{
		MinionDeathAnimation();
	}
}

void Hammer::Draw(sf::RenderWindow & window, Texture * texture)
{
	if(minionState != -2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX() - 4, (float)yMinion - 4));
}

void Hammer::MinionPhysics()
{
	if (jumpState == NhayLen)
	{
		PhysicsState1();
	}
	else
	{
		currentFallingSpeed *= 1.06f;

		if (currentFallingSpeed > startJumpSpeed)
			currentFallingSpeed = startJumpSpeed;

		yMinion += currentFallingSpeed;

		if (yMinion > Window::gameHeight)
			minionState = -1;
	}
}

void Hammer::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect())
		SetMinionState(-2);
	else
		Window::GetMap()->PlayerDeath();
}
