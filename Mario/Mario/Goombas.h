#pragma once

#ifndef _GOOMBAS
#define _GOOMBAS

#include "Minion.h"

class Goombas : public Minion
{
public:
	Goombas(float xMinion, float yMinion, int id, bool moveDirection);
	~Goombas();

	void Update(unsigned int time);
	void Draw(sf::RenderWindow& window, Texture* texture);

	void CollisionWithPlayer(bool top);

	void SetMinionState(int minionState);
};

#endif
