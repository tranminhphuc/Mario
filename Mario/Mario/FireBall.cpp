#include "FireBall.h"
#include "Windows.h"

FireBall::FireBall(int x, int y, int radius, int sliceID, bool moveDirection)
{
	centerX = x;
	centerY = y;

	width = 16;
	height = 16;

	id = 25;

	this->radius = radius;
	this->moveDirection = moveDirection;
	this->sliceID = sliceID;
	this->slice = 2 * 3.14 / 360;

	angle = slice * sliceID;

	xMinion = (float)(x + radius * cos(angle));
	yMinion = (float)(y + radius * sin(angle));

	this->collisionOnlyWithPlayer = true;
}

FireBall::~FireBall()
{
}

void FireBall::Update(unsigned int time)
{
	if (moveDirection)
	{
		angle = slice * sliceID;

		xMinion = (float)(centerX + radius * cos(angle));
		yMinion = (float)(centerY + radius * sin(angle));

		if (sliceID <= 0)
			sliceID = 360;
		else
			sliceID -= 2;
	}
	else
	{
		angle = slice * sliceID;

		xMinion = (float)(centerX + radius * cos(angle));
		yMinion = (float)(centerY + radius * sin(angle));

		if (sliceID > 359)
			sliceID = 0;
		else
			sliceID += 2;
	}
}

void FireBall::Draw(sf::RenderWindow & window, Texture * texture)
{
	texture->Draw(window, sf::Vector2f(xMinion + Window::GetMap()->GetX(), yMinion));
}

void FireBall::MoveX() { }

void FireBall::MinionPhysics() { }

void FireBall::CollisionWithPlayer(bool top)
{
	Window::GetMap()->PlayerDeath();
}