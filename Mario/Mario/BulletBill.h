#pragma once

#ifndef _BULLETBILL
#define _BULLETBILL

#include "Minion.h"

class BulletBill : public Minion
{
public:
	int minX, maxX;

	BulletBill(int xMinion, int yMinion, int minionState, bool moveDirection);
	~BulletBill();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void CollisionWithPlayer(bool top);
};

#endif
