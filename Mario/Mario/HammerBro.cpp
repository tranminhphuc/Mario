#include "HammerBro.h"
#include "Windows.h"
#include "Game.h"

HammerBro::HammerBro(int xMinion, int yMinion)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion + 18;

	moveDir = true;
	moveDirection = true;
	moveSpeed = 1;
	minionState = 0;

	width = 32;
	height = 48;

	moveDistance = 16;
	newY = true;

	nextJumpFrameID = rand() % 175 + 175;
	currentJumpDistance = 0;
	jumpDistance = 0;

	hammerID = 0;
	nextHammerFrameID = 65;
}

HammerBro::~HammerBro()
{
}

void HammerBro::Update()
{
	if (minionState != -2)
	{
		moveDirection = !(Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2 > xMinion + width / 2);

		if (moveDistance > 0)
		{
			moveDistance -= 0.5f;

			if (jumpState == 1)
				xMinion += moveDir ? -0.5f : 0.5f;

			if (moveDir)
			{
				if (!CheckCollisionLB(-moveSpeed, -2) && CheckCollisionLT(-moveSpeed, 2))
					xMinion += -0.5f;
			}
			else
			{
				if (!CheckCollisionRB(moveSpeed, -2) && !CheckCollisionRT(moveSpeed, 2))
					xMinion += 0.5f;
			}
		}
		else
		{
			moveDistance = 1 * 32 + 16;
			moveDir = !moveDir;
		}

		if (currentJumpDistance > 0)
		{
			if (newY)
			{
				yMinion -= 4;
				currentJumpDistance -= 4;
			}
			else
			{
				if (jumpDistance > 0)
				{
					yMinion -= 4;
					jumpDistance -= 4;
				}
				else
				{
					yMinion += 4;
					currentJumpDistance -= 4;
				}
			}
		}
		else if (nextJumpFrameID < 0)
		{
			currentJumpDistance = 4 * 43 + 16;
			jumpDistance = 16;
			nextJumpFrameID = rand() % 295 + 215;
			jumpState = NhayLen;

			if (yMinion + height < Game::gameHeight - 4 * 32)
				newY = rand() % 3 == 0;
			else
				newY = true;
		}
		else
		{
			nextJumpFrameID--;
			jumpState = NhayXuong;
		}

		if (nextHammerFrameID < 0)
		{
			nextHammerFrameID = rand() % 95 + 95;

			if (hammerID < 2 - rand() % 2)
			{
				hammerID++;
				nextHammerFrameID /= 4;
			}
			else
			{
				hammerID = 0;
			}
		}
		else
		{
			MinionDeathAnimation();
		}
	}
}

void HammerBro::Draw(sf::RenderWindow & window, Texture * texture)
{
	if(minionState != -2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion - 18));
}

void HammerBro::MinionPhysics()
{
	if (jumpState != NhayLen)
	{
		if (!CheckCollisionLB(2, 2) && !CheckCollisionRB(-2, 2))
			PhysicsState2();
		else
			jumpState = TrenMatDat;
	}
}

void HammerBro::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect() || top)
		SetMinionState(-2);
	else
		Window::GetMap()->PlayerDeath();
}
