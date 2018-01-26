#include "Plant.h"
#include "Windows.h"

Plant::Plant(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

Plant::~Plant()
{
}

void Plant::Update(unsigned int time)
{
}

void Plant::Draw(sf::RenderWindow & window, Texture * texture)
{
	texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX() - 2, (float)yMinion - 6));
}
