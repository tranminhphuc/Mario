#include "Fire.h"
#include "Windows.h"

Fire::Fire(int xMinion, int yMinion, int toYMinion)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;
	this->toYMinion = toYMinion;

	moveDirection = true;

	width = 48;
	height = 10;

	minionSpawned = false;
}

Fire::~Fire()
{
}

void Fire::Update()
{
	xMinion -= 2;

	if (xMinion += width < 0)
		minionState = -1;

	if (toYMinion > yMinion)
		yMinion++;
	else
		yMinion--;
}

void Fire::Draw(sf::RenderWindow & window, Texture * texture)
{
	texture->Draw(window, sf::Vector2f(xMinion + Window::GetMap()->GetX(), yMinion - 4));
}
