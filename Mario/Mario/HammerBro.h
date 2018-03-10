#pragma once

#ifndef _HAMMERBRO
#define _HAMMERBRO

#include "Minion.h"

class HammerBro : public Minion
{
private:
	bool moveDir;
	float moveDistance;

	int nextJumpFrameID;
	bool newY;

	int hammerID;
	int nextHammerFrameID;
public:
	HammerBro(int xMinion, int yMinion);
	~HammerBro();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void MinionPhysics();

	void CollisionWithPlayer(bool top);
};

#endif
