#include "Flower.h"
#include "Windows.h"

Flower::Flower(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

Flower::~Flower()
{
}

void Flower::Update()
{
}

void Flower::Draw(sf::RenderWindow & window, Texture * texture)
{
	if (minionState >= 0)
	{
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion + 2));
	}
}
