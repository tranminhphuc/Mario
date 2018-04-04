#pragma once

#ifndef _FIREBALL
#define _FIREBALL

#include "Minion.h"

class FireBall : public Minion
{
private:
	int radius;
	double angle;

	int centerX, centerY;
	double slice;
	
	int sliceID;
public:
	FireBall(int x, int y, int radius, int sliceID, bool moveDirection);
	~FireBall();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);

	void MoveX();
	void MinionPhysics();

	void CollisionWithPlayer(bool top);
};

#endif
