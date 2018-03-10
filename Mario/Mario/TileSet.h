#pragma once

#ifndef _TILESET
#define _TILESET

class TileSet
{
private:
	int id;
	int numberOfCoin;
	int y;

	bool mushroom;
	bool star;
	bool powerUp;

	bool blockAnimation;
	bool yDirection;
public:
	TileSet(int tileID);
	~TileSet();
	void SetID(int tileID);
	int GetID();
	int GetY();
	int getNumberOfCoin();
	void SetNumberOfCoin(int numberOfCoin);
	bool GetMushroom();
	void SetMustroom(bool mushroom);
	bool GetStar();
	void SetStar(bool star);
	bool GetPowerUp();
	void SetPowerUp(bool powerUp);

	void StartBlockAnimation();

	int MoveY();
};

#endif
