#pragma once

#ifndef _FLOWER
#define _FLOWER

#include "Minion.h"

class Flower : public Minion
{
private:
	bool inSpawnState;
	int inSpawnY;
	int x, y;
public:
	Flower(int xMinion, int yMinion, int x, int y);
	~Flower();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	bool UpdateMinion();

	void CollisionWithPlayer(bool top);
};

#endif
