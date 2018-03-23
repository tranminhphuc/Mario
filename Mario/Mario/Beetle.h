#pragma once

#ifndef _BETTLE
#define _BETTLE

#include "Minion.h"

class Beetle : public Minion
{
public:
	Beetle(int xMinion, int yMinion, bool moveDirection);
	~Beetle();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void CollisionWithPlayer(bool top);
	void CollisionEffect();

	void SetMinionState(int minionState);
};

#endif
