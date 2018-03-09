#pragma once

#ifndef _FIRE
#define _FIRE

#include "Minion.h"

class Fire : public Minion
{
private:
	int toYMinion;
public:
	Fire(int xMiinon, int yMinion, int toYMinion);
	~Fire();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
