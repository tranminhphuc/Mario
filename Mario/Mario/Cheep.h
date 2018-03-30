#pragma once

#ifndef _CHEEP
#define _CHEEP

#include "Minion.h"

class Cheep : public Minion
{
private:
	bool moveYDir;
public:
	Cheep(int xMinion, int yMinion, int minionType, int moveSpeed, bool moveDirection = false);
	~Cheep();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void MinionPhysics();
	void CollisionWithPlayer(bool top);

	void ChangeDistance(float y, float distance);
};

#endif
