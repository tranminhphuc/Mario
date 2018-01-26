#include "Lakito.h"
#include "Windows.h"

Lakito::Lakito(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

Lakito::~Lakito()
{
}

void Lakito::Update()
{
}

void Lakito::Draw(sf::RenderWindow & window, Texture * texture)
{
	if(minionState != -2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion - 16));
}

void Lakito::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect() || top)
		SetMinionState(-2);
	else if (!end)
		Window::GetMap()->PlayerDeath();
}
