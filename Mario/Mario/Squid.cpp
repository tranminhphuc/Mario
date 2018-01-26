#include "Squid.h"
#include "Windows.h"

Squid::Squid(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

Squid::~Squid()
{
}

void Squid::Update()
{
}

void Squid::Draw(sf::RenderWindow & window, Texture * texture)
{
	texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion));
}

void Squid::CollisionWithPlayer(bool top)
{
	Window::GetMap()->PlayerDeath();
}

void Squid::ChangeID()
{
	switch (id)
	{
	case 28:
		id = 29;
		height = 28;
		break;
	default:
		id = 28;
		height = 28;
		break;
	}
}
