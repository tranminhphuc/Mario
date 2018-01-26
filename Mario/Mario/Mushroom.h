#pragma once

#ifndef _MUSHROOM
#define _MUSHROOM

#include "Minion.h"

class Mushroom : public Minion
{
private:
	float x, y;
	bool powerUp;
	bool inSpawnState;
	int inSpawnY;
public:
	Mushroom(int xMinion, int yMinion, bool powerUp, float x, float y);
	~Mushroom();

	void Update();
	bool UpdateMinion();

	void Draw(sf::RenderWindow& window, Texture* texture);

	void CollisionWithPlayer();

	void SetMinionState(int minionState);
};

#endif
