#pragma once

#ifndef _SQUID
#define _SQUID

#include "Minion.h"

class Squid : public Minion
{
public:
	Squid(int xMinion, int yMinion);
	~Squid();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);
};

#endif
