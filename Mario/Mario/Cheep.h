#pragma once

#ifndef _CHEEP
#define _CHEEP

#include "Minion.h"

class Cheep : public Minion
{
public:
	Cheep(int xMinion, int yMinion);
	~Cheep();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
