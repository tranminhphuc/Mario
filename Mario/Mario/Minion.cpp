#include "Minion.h"
#include "Windows.h"
#include "Game.h"

Minion::Minion()
{
	width = height = 32;

	moveDirection = true;
	moveSpeed = 1;

	startJumpSpeed = 6.65f;
	currentJumpSpeed = 0;
	jumpDistance = 0;
	currentJumpDistance = 0;

	jumpState = TrenMatDat;
	currentFallingSpeed = 2.2f;

	deadTime = -1;

	minionSpawned = false;
	onAnotherMinion = false;
	collisionOnlyWithPlayer = false;
}

Minion::~Minion()
{
}

void Minion::Update() { }

void Minion::Draw()
{
}

void Minion::MoveX()
{
	if (moveDirection)
	{
		if (CheckCollisionLB(-moveSpeed, -2) || CheckCollisionLT(-moveSpeed, 2))
		{
			moveDirection = !moveDirection;
		}
		else
		{
			xMinion -= (float)(jumpState == TrenMatDat ? moveSpeed : moveSpeed / 2);
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
			xMinion += (float)(jumpState == TrenMatDat ? moveSpeed : moveSpeed / 2);
		}
	}

	if (xMinion < -width)
	{
		minionState = -1;
	}
}

void Minion::MoveY(int distance)
{
	if (distance > 0)
	{
		if (!CheckCollisionLB(2, distance) && !CheckCollisionRB(-2, distance))
		{
			yMinion += distance;
		}
		else
		{
			if (jumpState == NhayLen)
				jumpState = NhayXuong;

			MoveY(distance - 1);
		}
	}
	else if(distance < 0)
	{
		if (CheckCollisionLT(2, distance) && !CheckCollisionRT(-2, distance))
		{
			yMinion += distance;
		}
		else
		{
			if (jumpState == NhayLen)
				jumpState = NhayXuong;

			MoveY(distance + 1);
		}
	}

	if ((int)yMinion % 2 == 1)
		yMinion += 1;
}

bool Minion::UpdateMinion()
{
	if (!minionSpawned)
		Spawn();
	else
		MinionPhysics();

	return minionSpawned;
}

void Minion::MinionPhysics()
{
	if (jumpState == NhayLen)
	{
		PhysicsState1();
	}
	else
	{
		if (!CheckCollisionLB(2, 2) && !CheckCollisionRB(-2, 2) && !onAnotherMinion)
		{
			PhysicsState2();
		}
		else
		{
			jumpState = TrenMatDat;
			onAnotherMinion = false;
		}
	}
}

void Minion::CollisionEffect()
{
	if (minionSpawned)
		moveDirection = !moveDirection;
}

void Minion::MinionDeathAnimation()
{
	xMinion += (moveDirection ? -1.5f : 1.5f);
	yMinion += 2 * (deadTime > 8 ? -1 : deadTime > 2 ? 1 : 4.25f);

	if (deadTime > 0)
		deadTime--;

	if (yMinion > Game::gameHeight)
		minionState = -1;
}

void Minion::CollisionWithPlayer() { }

void Minion::CollisionWithAnotherMinion() { }

void Minion::LockMinion() { }

void Minion::SetMinionState(int minionState)
{
	this->minionState = minionState;

	if (minionState == -2)
	{
		deadTime = 16;
		yMinion -= (float)height / 4;
		collisionOnlyWithPlayer = true;
	}
}

void Minion::GetPowerUp()
{
}

void Minion::PhysicsState1()
{
	MoveY(-(int)currentJumpSpeed);

	currentJumpDistance += currentJumpSpeed;
	currentJumpSpeed *= (currentJumpDistance / jumpDistance > 0.75f ? 0.972f : 0.986f);

	if (currentJumpSpeed < 2.5f)
		currentJumpSpeed = 2.5f;

	if (jumpDistance <= currentJumpDistance)
	{
		jumpState = NhayXuong;
	}
}

void Minion::PhysicsState2()
{
	currentFallingSpeed *= 1.06f;

	if (currentFallingSpeed > startJumpSpeed)
		currentFallingSpeed = startJumpSpeed;

	MoveY((int)currentFallingSpeed);

	jumpState = NhayXuong;

	if (yMinion > Game::gameHeight)
	{
		minionState = -1;
	}
}

void Minion::StartJump(int distance)
{
	jumpState = NhayLen;
	currentJumpSpeed = startJumpSpeed;
	jumpDistance *= 32 * distance * 16.0f;
	currentJumpDistance = 0;
}

void Minion::ResetJump()
{
	jumpState = TrenMatDat;
	currentFallingSpeed = 2.7f;
}

void Minion::Spawn()
{
	if (xMinion >= -Window::getMap()->GetX() && -Window::getMap()->GetX() + Game::gameWidth || xMinion + width >= -Window::getMap()->GetX() && xMinion + width <= -Window::getMap()->GetX() + Game::gameWidth)
	{
		minionSpawned = true;
	}
}

float Minion::GetX()
{
	return xMinion;
}

float Minion::GetY()
{
	return yMinion;
}

void Minion::SetY(float y)
{
	this->yMinion = y;
}

int Minion::GetMinionState()
{
	return minionState;
}

bool Minion::CheckCollisionLB(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(xMinion - Window::getMap()->GetX() + distanceX), (int)(yMinion + height + distanceY));
}

bool Minion::CheckCollisionLT(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(xMinion - Window::getMap()->GetX() + distanceX), (int)(yMinion + distanceY));
}

bool Minion::CheckCollisionRB(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(xMinion - Window::getMap()->GetX() + width + distanceX), (int)(yMinion + height + distanceY));
}

bool Minion::CheckCollisionRT(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(xMinion - Window::getMap()->GetX() + width + distanceX), (int)(yMinion + distanceY));
}

bool Minion::CheckCollisionLC(int distance)
{
	return Window::getMap()->CheckObject((int)(xMinion - Window::getMap()->GetX() + width + distance), (int)(yMinion + (width / 2)));
}

bool Minion::CheckCollisionRC(int distance)
{
	return Window::getMap()->CheckObject((int)(xMinion - Window::getMap()->GetX() + distance), (int)(yMinion + (width / 2)));
}

