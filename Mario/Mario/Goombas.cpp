#include "Goombas.h"
#include "Windows.h"

Goombas::Goombas(int xMinion, int yMinion, int id, bool moveDirection)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;
	this->id = id;
	this->moveDirection = moveDirection;
}

Goombas::~Goombas()
{
}

void Goombas::Update()
{
	if (minionState == 0)
	{
		MoveX();
	}
	else if (minionState == -2)
	{
		MinionDeathAnimation();
	}
	else if (Window::GetTime() - 500 >= (unsigned)deadTime)
	{
		minionState = -1;
	}
}

void Goombas::Draw(sf::RenderWindow& window, Texture* texture)
{
	if (minionState != 2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion + 2));
}

void Goombas::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect())
	{
		SetMinionState(-2);
	}
	else if (top)
	{
		if (minionState = 0)
		{
			minionState = 1;
			Window::GetMap()->GetPlayer()->ResetJump();
			Window::GetMap()->GetPlayer()->StartJump(1);
		}
	}
	else
	{
		Window::GetMap()->PlayerDeath();
	}
}

void Goombas::SetMinionState(int minionState)
{
	this->minionState = minionState;

	if (this->minionState == 1)
	{

	}

	Minion::SetMinionState(minionState);
}