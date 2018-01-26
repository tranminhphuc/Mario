#include "Hammer.h"
#include "Windows.h"
#include "Game.h"

Hammer::Hammer(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

Hammer::~Hammer()
{
}

void Hammer::Update()
{
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

		yMinion += (int)currentFallingSpeed;

		if (yMinion > Game::gameHeight)
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
