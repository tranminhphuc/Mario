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
	Koopa(int xMinion, int yMinion, int minionState, bool moveDirection);
	~Koopa();

	void Update(unsigned int time);
	void Draw();

	void MoveX();
	void MinionPhysics();

	void CollisionEffect();
	void CollisionWithPlayer(bool top);

	void SetMinionState(int minionState);
	void SetMinion();
};

#endif
