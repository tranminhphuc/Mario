#include "Mushroom.h"
#include "Windows.h"

Mushroom::Mushroom(int xMinion, int yMinion, bool powerUp, float x, float y)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
	this->powerUp = powerUp;
	//this->x = x;
	//this->y = y;

	this->moveSpeed = 2;
	this->inSpawnY = 30;
	this->inSpawnState = true;
	this->minionSpawned = false;
	this->moveDirection = false;
	this->collisionOnlyWithPlayer = true;
	this->minionState = 0;
}

Mushroom::~Mushroom()
{
}

void Mushroom::Update()
{
	if (inSpawnState)
	{
		if (inSpawnY <= 0)
		{
			inSpawnState = false;
		}
		else
		{
			if (yMinion > -5)
			{
				inSpawnY -= 2;
				yMinion -= 2;
			}
			else
			{
				inSpawnY -= 11;
				yMinion -= 1;
			}
		}
	}
	else
	{
		MoveX();
	}
}

bool Mushroom::UpdateMinion()
{
	if (!inSpawnState)
		MinionPhysics();

	return minionSpawned;
}

void Mushroom::Draw(sf::RenderWindow& window, Texture* texture)
{
	if (minionState >= 0)
	{
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion + 2));
	}
}

void Mushroom::CollisionWithPlayer()
{
	if (!inSpawnState && minionState == 0)
	{
		if (powerUp)
		{
			Window::GetMap()->GetPlayer()->SetLevel(Window::GetMap()->GetPlayer()->GetLevel() + 1);
		}
		else
		{
			Window::GetMap()->GetPlayer()->SetLive(Window::GetMap()->GetPlayer()->getLive() + 1);
		}

		minionState = -1;
	}
}

void Mushroom::SetMinionState(int minionState)
{
	
}
