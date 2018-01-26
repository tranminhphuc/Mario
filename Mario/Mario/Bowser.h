#pragma once

#ifndef _BOWSER
#define _BOWSER

#include "Minion.h"

class Bowser : public Minion
{
private:
	bool spawnHammer;

	int minBlockID, maxBlockID;
	bool moveDirection;

	int fireStart;
	int fireID;
public:
	Bowser(int xMinion, int yMinion);
	~Bowser();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void MinionPhysics();

	void CollisionWithPlayer(bool top);

	void CreateFire();
};

#endif
