#include "Koopa.h"
#include "Windows.h"

Koopa::Koopa(int xMinion, int yMinion, int id, int minionState, bool moveDirection)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion;
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

				if (yMinion >= Window::gameHeight)
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
	if (minionState != 2 && moveSpeed != 0)
		moveDirection = !moveDirection;
}

void Koopa::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect())
	{
		SetMinionState(-2);
	}
	else if (top)
	{
		if (minionState == 0 || minionState == 3)
		{
			minionState = 1;
			SetMinion();

			Window::GetMap()->GetPlayer()->ResetJump();
			Window::GetMap()->GetPlayer()->StartJump(1);
			Window::GetMap()->GetPlayer()->SetY(Window::GetMap()->GetPlayer()->GetY() - 4);
		}
		else if (minionState == 1)
		{
			minionState = 2;
			SetMinion();

			Window::GetMap()->GetPlayer()->ResetJump();
			Window::GetMap()->GetPlayer()->StartJump(1);
			Window::GetMap()->GetPlayer()->SetY(Window::GetMap()->GetPlayer()->GetY() - 4);
		}
		else
		{
			if (moveSpeed > 0)
			{
				moveSpeed = 0;
			}
			else
			{
				if ((xMinion + width) / 2 < (Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth()) / 2)
					moveDirection = true;
				else
					moveDirection = false;

				moveSpeed = 6;
			}

			Window::GetMap()->GetPlayer()->SetY(Window::GetMap()->GetPlayer()->GetY() - 4);
			Window::GetMap()->GetPlayer()->ResetJump();
			Window::GetMap()->GetPlayer()->StartJump(1);
		}
	}
	else
	{
		if (minionState == 2)
		{
			if (moveSpeed == 0)
			{
				moveDirection = (xMinion + width / 2 < Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2);
				
				if (moveDirection)
					xMinion -= Window::GetMap()->GetPlayer()->GetMoveSpeed() + 1;
				else
					xMinion += Window::GetMap()->GetPlayer()->GetMoveSpeed() + 1;

				moveSpeed = 6;
			}
			else
			{
				Window::GetMap()->PlayerDeath();
			}
		}
		else
		{
			Window::GetMap()->PlayerDeath();
		}
	}
}

void Koopa::SetMinionState(int minionState)
{
	this->minionState = minionState;

	if (this->minionState == 3)
		deadTime = Window::GetTime();

	Minion::SetMinionState(minionState);
}

void Koopa::SetMinion()
{
	switch (minionState)
	{
	case 0: case 3:
		width = 32;
		height = 32;
		break;
	case 1:
		width = 32;
		height = 32;
		break;
	case 2:
		width = 32;
		height = 32;
		moveSpeed = 0;
		break;
	}

	switch (id)
	{
	case 7:
		id = 4;
		break;
	case 14:
		id = 12;
		break;
	case 17:
		id = 15;
		break;
	case 4:
		id = 5;
		break;
	case 12:
		id = 13;
		break;
	case 15:
		id = 16;
		break;
	}
}
