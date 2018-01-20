#pragma once

#ifndef _HAMMER
#define _HAMMER

#include "Minion.h"

class Hammer : public Minion
{
public:
	Hammer(int xMinion, int yMinion);
	~Hammer();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
