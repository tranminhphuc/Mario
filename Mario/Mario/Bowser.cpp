#include "Bowser.h"
#include "Windows.h"

Bowser::Bowser(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

Bowser::~Bowser()
{
}

void Bowser::Update()
{
}

void Bowser::Draw(sf::RenderWindow & window, Texture * texture)
{
	texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion));
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
}
