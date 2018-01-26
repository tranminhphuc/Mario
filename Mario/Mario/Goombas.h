#pragma once

#ifndef _GOOMBAS
#define _GOOMBAS

#include "Minion.h"

class Goombas : public Minion
{
public:
	Goombas(int xMinion, int yMinion, int id, bool moveDirection);
	~Goombas();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void CollisionWithPlayer(bool top);

	void SetMinionState(int minionState);
};

#endif
