#include "Cheep.h"

Cheep::Cheep(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

Cheep::~Cheep()
{
}

void Cheep::Update(unsigned int time)
{
}

void Cheep::Draw(sf::RenderWindow & window, Texture * texture)
{
}

void Cheep::CollisionWithPlayer(bool top)
{
}
