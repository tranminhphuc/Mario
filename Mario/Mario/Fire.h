#pragma once

#ifndef _FIRE
#define _FIRE

#include "Minion.h"

class Fire : public Minion
{
public:
	Fire(int xMinon, int yMinion);
	~Fire();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
