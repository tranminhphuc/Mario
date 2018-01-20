#pragma once

#ifndef _PLANT
#define _PLANT

#include "Minion.h"

class Plant : public Minion
{
public:
	Plant(int xMinion, int yMinion);
	~Plant();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif