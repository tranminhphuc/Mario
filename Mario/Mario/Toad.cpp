#include "Toad.h"
#include "Windows.h"

Toad::Toad(int x, int y, bool peach)
{
	xMinion = (float)x;
	yMinion = (float)y;

	moveSpeed = 0;
	collisionOnlyWithPlayer = true;

	minionSpawned = true;
	id = peach ? 27 : 26;

	width = 32;
	height = 48;
}

Toad::~Toad()
{
}

void Toad::Draw(sf::RenderWindow & window, Texture * texture)
{
	texture->Draw(window, sf::Vector2f(xMinion + Window::GetMap()->GetX(), yMinion));
}
