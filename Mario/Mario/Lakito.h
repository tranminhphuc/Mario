#pragma once

#ifndef _LAKITO
#define _LAKITO

#include "Minion.h"

class Lakito : public Minion
{
public:
	Lakito(int xMinion, int yMinion);
	~Lakito();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
