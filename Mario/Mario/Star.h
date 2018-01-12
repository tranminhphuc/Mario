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
	Star(float xMinion, float yMinion, float x, float y);
	~Star();

	void Update();
	bool UpdateMinion();

	void Draw();

	void MinionPhysics();

	void CollisionWithPlayer();
	void SetMinionState(int minionState);
};

#endif
