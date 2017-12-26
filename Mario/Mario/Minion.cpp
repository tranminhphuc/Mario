#include "Minion.h"
#include "Windows.h"

Minion::Minion()
{
}

Minion::~Minion()
{
}

bool Minion::CheckCollisionLB(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(x - Window::getMap()->GetX() + distanceX), (int)(y + height + distanceY));
}

bool Minion::CheckCollisionLT(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(x - Window::getMap()->GetX() + distanceX), (int)(y + distanceY));
}

bool Minion::CheckCollisionRB(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(x - Window::getMap()->GetX() + width + distanceX), (int)(y + height + distanceY));
}

bool Minion::CheckCollisionRT(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(x - Window::getMap()->GetX() + width + distanceX), (int)(y + distanceY));
}

bool Minion::CheckCollisionLC(int distance)
{
	return Window::getMap()->CheckObject((int)(x - Window::getMap()->GetX() + width + distance), (int)(y + (width / 2)));
}

bool Minion::CheckCollisionRC(int distance)
{
	return Window::getMap()->CheckObject((int)(x - Window::getMap()->GetX() + distance), (int)(y + (width / 2)));
}

void Minion::Update()
{
}

void Minion::Draw()
{
}

void Minion::MoveX()
{
	if (moveDirection)
	{
		if (CheckCollisionLB(-moveSpeed, -2) || CheckCollisionLT(-moveSpeed, 2))
		{
			moveDirection = moveDirection;
		}
	}
	else
	{
		if (CheckCollisionRB(moveSpeed, 2) || CheckCollisionRT(moveSpeed, 2))
		{
			moveDirection = !moveDirection;
		}
	}
}

void Minion::moveY()
{
}

bool Minion::UpdateMinion()
{
	return false;
}

void Minion::MinionPhysics()
{
}
