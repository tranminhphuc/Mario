#include "TileSet.h"

TileSet::TileSet(int tileID)
{
	id = tileID;
	numberOfCoin = 0;
	mushroom = false;
	star = false;
	powerUp = true;

	blockAnimation = false;
	y = 0;
	yDirection = true;
}

TileSet::~TileSet()
{
}

void TileSet::SetID(int tileID)
{
	id = tileID;
}

int TileSet::GetID()
{
	return id;
}

int TileSet::GetY()
{
	return y;
}

int TileSet::getNumberOfCoin()
{
	return numberOfCoin;
}

void TileSet::SetNumberOfCoin(int numberOfCoin)
{
	this->numberOfCoin = numberOfCoin;
}

bool TileSet::GetMushroom()
{
	return mushroom;
}

void TileSet::SetMustroom(bool mushroom)
{
	this->mushroom = mushroom;
}

bool TileSet::GetStar()
{
	return star;
}

void TileSet::SetStar(bool star)
{
	this->star = star;
}

bool TileSet::GetPowerUp()
{
	return powerUp;
}

void TileSet::SetPowerUp(bool powerUp)
{
	this->powerUp = powerUp;
}

void TileSet::StartBlockAnimation()
{
	blockAnimation = true;
	y = 0;
	yDirection = true;
}

int TileSet::MoveY()
{
	if (blockAnimation)
	{
		if (yDirection)
		{
			if (y < 10)
			{
				if (y < 5)
					y += 2;
				else
					y += 1;
			}
			else
			{
				yDirection = false;
			}
		}
		else
		{
			if (y > 0)
			{
				if (y > 5)
					y -= 2;
				else
					y -= 1;
			}
			else
			{
				blockAnimation = false;
			}
		}
	}

	return y;
}
