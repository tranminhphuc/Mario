#include "Bowser.h"
#include "Windows.h"

Bowser::Bowser(int xMinion, int yMinion, bool spawHammer)
{
	srand((unsigned int)time(NULL));

	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;

	this->width = this->height = 64;

	this->id = 22;
	this->moveDirection = true;

	this->nextFireID = 1;
	this->nextJumpID = 128;

	this->minionSpawned = true;

	this->minBlockID = xMinion / 32 - 4;
	this->maxBlockID = yMinion / 32 + 4;

	this->collisionOnlyWithPlayer = true;

	this->fireStart = yMinion - 32;
	this->fireID = 0;

	this->nextHammerID = 128;
	this->numOfHammer = 3 + rand() % 6;
	this->spawnHammer = spawnHammer;
}

Bowser::~Bowser()
{
}

void Bowser::Update()
{
	moveDirection = Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() < xMinion + width;
}

void Bowser::Draw(sf::RenderWindow & window, Texture * texture)
{
	texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion));

	if (spawnHammer)
	{
		if (nextHammerID <= 24 && moveDirection)
			Window::GetMap()->GetObject(61)->GetAnimation()->getTexture()->Draw(window, sf::Vector2f(xMinion + Window::GetMap()->GetX() + 4, yMinion - 20));
	}
}

void Bowser::MinionPhysics()
{
	if (jumpState == NhayLen)
	{
		if (jumpDistance <= currentJumpDistance + 16)
		{
			yMinion -= 1;
			currentJumpDistance += 1;
		}
		else
		{
			yMinion -= 2;
			currentJumpDistance += 2;
		}

		if (jumpDistance <= currentJumpDistance)
		{
			jumpState = NhayXuong;
			currentJumpDistance = 0;
		}
	}
	else
	{
		if (!CheckCollisionLB(2, 2) && CheckCollisionRB(-2, 2))
		{
			if (currentJumpDistance < 16)
			{
				currentJumpDistance += 1;
				MoveY(1);
			}
			else
			{
				MoveY(2);
			}
		}
		else
		{
			jumpState = TrenMatDat;
		}
	}
}

void Bowser::CollisionWithPlayer(bool top)
{
	Window::GetMap()->PlayerDeath();
}

void Bowser::CreateFire()
{
	Window::GetMap()->AddFire((int)xMinion - 40, (int)yMinion + 16, fireStart + 16 * (rand() % 4 + 1) + 6);
	fireID++;

	if (fireID > 2)
	{
		nextFireID += 88 + rand() % 110;
		fireID = 0;
	}
}
