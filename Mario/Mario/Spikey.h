#pragma once

#ifndef _SPIKEY
#define _SPIKEY

#include "Minion.h"

class Spikey : public Minion
{
public:
	Spikey(int xMinion, int yMinion);
	~Spikey();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void MinionPhysics();

	void CollisionWithPlayer(bool top);
};

#endif
