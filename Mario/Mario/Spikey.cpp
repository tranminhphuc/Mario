#include "Spikey.h"
#include "Windows.h"

Spikey::Spikey(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

Spikey::~Spikey()
{
}

void Spikey::Update()
{
	if (minionState == 0)
		MoveX();
	else if (minionState == -2)
		MinionDeathAnimation();
}

void Spikey::Draw(sf::RenderWindow & window, Texture * texture)
{
	if(minionState != -2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion - 4));
}

void Spikey::MinionPhysics()
{
	if (jumpState == NhayLen)
	{
		PhysicsState1();
	}
	else
	{
		if (!CheckCollisionLB(2, 2) && !CheckCollisionRB(-2, 2))
		{
			PhysicsState2();
		}
		else
		{
			jumpState = TrenMatDat;
			onAnotherMinion = false;

			if (id == 52)
			{
				id = 51;
				moveDirection = xMinion + width / 2 > Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2;
				moveSpeed = 1;
			}
		}
	}
}

void Spikey::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect())
		SetMinionState(-2);
	else
		Window::GetMap()->PlayerDeath();
}
