#pragma once

#ifndef _TOAD
#define _TOAD

#include "Minion.h"

class Toad : public Minion
{
public:
	Toad(int x, int y, bool peach);
	~Toad();

	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
