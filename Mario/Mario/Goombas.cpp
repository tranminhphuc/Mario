#include "Goombas.h"
#include "Windows.h"

Goombas::Goombas(float xMinion, float yMinion, int id, bool moveDirection)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
	this->id = id;
	this->moveDirection = moveDirection;
}

Goombas::~Goombas()
{
}

void Goombas::Update(unsigned int time)
{
	if (minionState == 0)
	{
		MoveX();
	}
	else if (minionState == -2)
	{
		MinionDeathAnimation();
	}
	else if (time - 500 >= (unsigned)deadTime)
	{
		minionState = -1;
	}
}

void Goombas::Draw(sf::RenderWindow& window, Texture* texture)
{
	if (minionState != 2)
		texture->Draw(window, sf::Vector2f(xMinion + Window::getMap()->GetX(), yMinion + 2));
}

void Goombas::CollisionWithPlayer(bool top)
{
	//if (Window::getMap()->GetPlayer()->GetStarEffect())
	//{
	//	SetMinionState(-2);
	//}
	//else if (top)
	//{
	//	if (minionState = 0)
	//	{
	//		minionState = 1;
	//		//Window::getMap()->GetPlayer()->ResetJump();
	//		//Window::getMap()->GetPlayer()->StartJump(1);
	//	}
	//}
	//else
	//{
	//	//Window::getMap()->PlayerDeath();
	//}
}

void Goombas::SetMinionState(int minionState)
{
	this->minionState = minionState;

	if (this->minionState == 1)
	{

	}

	Minion::SetMinionState(minionState);
}
