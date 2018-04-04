#pragma once

#ifndef _STAR
#define _STAR

#include "Minion.h"

class Star: public Minion
{
private:
	bool inSpawnState;
	int inSpawnY;
	float x, y;
public:
	Star(int xMinion, int yMinion, int x, int y);
	~Star();

	void Update();
	bool UpdateMinion();

	void Draw(sf::RenderWindow& window, Texture* texture);

	void MinionPhysics();

	void CollisionWithPlayer();
};

#endif
