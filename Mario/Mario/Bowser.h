#pragma once

#ifndef _BOWSER
#define _BOWSER

#include "Minion.h"

class Bowser : public Minion
{
private:
	int nextJumpID;

	bool spawnHammer;
	int nextHammerID, numOfHammer;

	int minBlockID, maxBlockID;
	bool moveDirection;

	int fireStart;
	int fireID;

	int nextFireID;
public:
	Bowser(int xMinion, int yMinion, bool spawHammer);
	~Bowser();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void MinionPhysics();

	void CollisionWithPlayer(bool top);

	void CreateFire();
};

#endif
