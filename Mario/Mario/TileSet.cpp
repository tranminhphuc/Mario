#include "TileSet.h"

TileSet::TileSet(int tileID)
{
	id = tileID;
	numberOfCoin = 0;
	mushroom = false;
	star = false;
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
