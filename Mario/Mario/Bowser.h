#pragma once

#ifndef _BOWSER
#define _BOWSER

#include "Minion.h"

class Bowser : public Minion
{
public:
	Bowser(int xMinion, int yMinion);
	~Bowser();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
