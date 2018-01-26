#pragma once

#ifndef _FLOWER
#define _FLOWER

#include "Minion.h"

class Flower : public Minion
{
public:
	Flower(int xMinion, int yMinion);
	~Flower();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
