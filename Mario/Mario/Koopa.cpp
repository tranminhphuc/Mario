#include "Koopa.h"
#include "Windows.h"
#include "Game.h"

Koopa::Koopa(int xMinion, int yMinion, int id, int minionState, bool moveDirection)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
	this->id = id;
	this->minionState = minionState;
	this->moveDirection = moveDirection;
	this->flyDirection = moveDirection;

	this->moveSpeed = 1;

	switch (minionState)
	{
	case 0: case 1:
		this->width = 32;
		this->height = 32;
		break;
	case 2:
		this->width = 32;
		this->height = 32;
		this->moveSpeed = 0;
		break;
	case 3:
		this->width = 32;
		this->height = 32;
		this->moveDirection = true;
		break;
	}

	this->distance = 7 * 32;
}

Koopa::~Koopa()
{
}

void Koopa::Update()
{
	if (minionState == 0)
	{
		MoveX();

		if (jumpState == TrenMatDat)
			StartJump(1);
	}
	else if (minionState == 1 || minionState == 2)
	{
		MoveX();
	}
	else if (minionState == -2)
	{
		MinionDeathAnimation();
	}
}

void Koopa::Draw(sf::RenderWindow& window, Texture* texture)
{
	if (minionState != -2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion + (minionState <= 1 ? -14 : 2)));
}

void Koopa::MoveX()
{
	if (moveDirection)
	{
		if (CheckCollisionLB(-moveSpeed, -2) || CheckCollisionLT(-moveSpeed, 2))
		{
			moveDirection = !moveDirection;
		}
		else
		{
			if (minionState == 1 && (!CheckCollisionLB(width / 2, 2) && CheckCollisionRB(width / 2, 2)))
			{
				moveDirection = !moveDirection;
				xMinion += moveSpeed;
			}
			else
			{
				xMinion -= moveSpeed;
			}
		}
	}
	else
	{
		if (CheckCollisionRB(moveSpeed, -2) || CheckCollisionRT(moveSpeed, 2))
		{
			moveDirection = !moveDirection;
		}
		else
		{
			if (minionState == 1 && (CheckCollisionLB(-width / 2, 2) && !CheckCollisionRB(-width / 2, 2)))
			{
				moveDirection = !moveDirection;
				xMinion -= moveSpeed;
			}
			else
			{
				xMinion += moveSpeed;
			}
		}
	}

	if (xMinion < -width)
		minionState = -1;
}

void Koopa::MinionPhysics()
{
	if (minionState == 3)
	{
		if (flyDirection)
		{
			if (distance > 0)
			{
				yMinion -= 2;
				distance -= 2;
			}
			else
			{
				distance = 7 * 32;
				flyDirection = !flyDirection;
			}
		}
		else
		{
			if (distance > 0)
			{
				yMinion += 2;
				distance -= 2;
			}
			else
			{
				distance = 7 * 32;
				flyDirection = !flyDirection;
			}
		}
	}
	else if(jumpState == NhayLen)
	{
		if (minionState == 0)
		{
			MoveY(-2);
			currentJumpDistance += 2;

			if (jumpDistance <= currentJumpDistance)
				jumpState = NhayXuong;
		}
		else
		{
			PhysicsState1();
		}
	}
	else
	{
		if (!CheckCollisionLB(2, 2) && !CheckCollisionRB(-2, 2) && !onAnotherMinion)
		{
			if (minionState == 0)
			{
				MoveY(2);
				jumpState = NhayXuong;

				if (yMinion >= Game::gameHeight)
					minionState = -1;
			}
			else
			{
				PhysicsState2();
			}
		}
		else
		{
			jumpState = TrenMatDat;
			onAnotherMinion = false;
		}
	}
}

void Koopa::CollisionEffect()
{
}

void Koopa::CollisionWithPlayer(bool top)
{
}

void Koopa::SetMinionState(int minionState)
{
}

void Koopa::SetMinion()
{
}
