#pragma once

#ifndef _SQUID
#define _SQUID

#include "Minion.h"

class Squid : public Minion
{
public:
	Squid(int xMinion, int yMinion);
	~Squid();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void CollisionWithPlayer(bool top);

	void ChangeID();
};

#endif
