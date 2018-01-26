#pragma once

#ifndef _KOPPA
#define _KOPPA

#include "Minion.h"

class Koopa : public Minion
{
private:
	int distance;
	bool flyDirection;
public:
	Koopa(int xMinion, int yMinion, int id, int minionState, bool moveDirection);
	~Koopa();

	void Update();
	void Draw(sf::RenderWindow& window, Texture* texture);

	void MoveX();
	void MinionPhysics();

	void CollisionEffect();
	void CollisionWithPlayer(bool top);

	void SetMinionState(int minionState);
	void SetMinion();
};

#endif
