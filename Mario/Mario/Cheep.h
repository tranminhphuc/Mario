#pragma once

#ifndef _CHEEP
#define _CHEEP

#include "Minion.h"

class Cheep : public Minion
{
private:
	bool moveY, moveYDir;
public:
	Cheep(int xMinion, int yMinion, int minionType, int moveSpeed, bool moveDirection = false);
	~Cheep();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);

	void CollisionWithPlayer(bool top);
};

#endif
