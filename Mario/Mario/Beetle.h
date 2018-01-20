#pragma once

#ifndef _BETTLE
#define _BETTLE

#include "Minion.h"

class Beetle : public Minion
{
public:
	Beetle(int xMinion, int yMinion, bool moveDirection);
	~Beetle();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
