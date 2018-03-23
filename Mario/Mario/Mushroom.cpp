#include "Mushroom.h"
#include "Windows.h"

Mushroom::Mushroom(int xMinion, int yMinion, bool powerUp, int x, int y)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;

	this->powerUp = powerUp;
	this->x = x;
	this->y = y;

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
				inSpawnY -= 1;
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

		if (inSpawnState)
			Window::GetMap()->GetObject(Window::GetMap()->GetMapType() == 0 || Window::GetMap()->GetMapType() == 4 ? 9 : 56)->GetAnimation()->getTexture()->Draw(window, sf::Vector2f(xMinion + Window::GetMap()->GetX(), yMinion + (32 - inSpawnY) - Window::GetMap()->GetTile(x, y)->GetY() + 2));
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
