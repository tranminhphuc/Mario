#pragma once

#ifndef _BULLETBILL
#define _BULLETBILL

#include "Minion.h"

class BulletBill : public Minion
{
public:
	BulletBill(int xMinion, int yMinion);
	~BulletBill();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void CollisionWithPlayer(bool top);
};

#endif
