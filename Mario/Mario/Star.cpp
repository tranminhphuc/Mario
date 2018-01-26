#include "Star.h"
#include "Windows.h"

Star::Star(int xMinion, int yMinion, float x, float y)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
	this->x = x;
	this->y = y;

	this->collisionOnlyWithPlayer = true;

	this->moveDirection = false;
	this->moveSpeed = 3;

	this->inSpawnState = true;
	this->minionSpawned = true;
	this->inSpawnY = 30;
	this->startJumpSpeed = 4;

	this->x = x;
	this->y = y;

	this->width = 28;
	this->height = 32;
}

Star::~Star()
{
}

void Star::Update()
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
		if (jumpState == TrenMatDat)
		{
			StartJump(1);
			jumpDistance = 32;
		}

		MoveX();
	}
}

bool Star::UpdateMinion()
{
	if (!inSpawnState)
		MinionPhysics();

	return minionSpawned;
}

void Star::Draw(sf::RenderWindow& window, Texture* texture)
{
	texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion + 2));
}

void Star::MinionPhysics()
{
	if (jumpState == NhayLen)
	{
		if (minionState == 0)
		{
			MoveY(-4 + (currentJumpDistance > 64 ? 2 : 0));
			currentJumpDistance += 2;

			if (jumpDistance <= currentJumpDistance)
				jumpState = NhayXuong;
		}
	}
	else
	{
		if (!CheckCollisionLB(2, 2) && !CheckCollisionRB(-2, 2))
			PhysicsState2();
		else
			jumpState = TrenMatDat;
	}
}

void Star::CollisionWithPlayer()
{
	if (!inSpawnState)
	{
		//Window::getMap()->GetPlayer()->
		minionState = -1;
	}
}

void Star::SetMinionState(int minionState)
{
}
