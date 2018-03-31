#pragma once

#ifndef _LAKITO
#define _LAKITO

#include "Minion.h"

class Lakito : public Minion
{
private:
	int maxX;
	bool end;
	bool followPlayer;
public:
	Lakito(int xMinion, int yMinion, int maxX);
	~Lakito();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void MinionPhysics();
	void CollisionWithPlayer(bool top);
};

#endif
