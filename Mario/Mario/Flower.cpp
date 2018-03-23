#include "Flower.h"
#include "Windows.h"

Flower::Flower(int xMinion, int yMinion, int x, int y)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;

	moveSpeed = 2;
	inSpawnState = true;
	minionSpawned = true;
	inSpawnY = 32;
	moveDirection = false;
	collisionOnlyWithPlayer = true;

	this->x = x;
	this->y = y;
}

Flower::~Flower()
{
}

void Flower::Update()
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
}

void Flower::Draw(sf::RenderWindow & window, Texture * texture)
{
	if (minionState >= 0)
	{
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion + 2));
	}
}

bool Flower::UpdateMinion()
{
	return minionSpawned;
}

void Flower::CollisionWithPlayer(bool top)
{
	if (!inSpawnState && minionState >= 0)
	{
		Window::GetMap()->GetPlayer()->SetLevel(Window::GetMap()->GetPlayer()->GetLevel() + 1);
		minionState = -1;
	}
}
