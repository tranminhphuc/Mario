#pragma once

#ifndef _MINION
#define _MINION

#include "Library.h"

class Minion
{
private:
	float x, y;
	int width, height;

	bool moveDirection;
	int moveSpeed;

	bool CheckCollisionLB(int distanceX, int distanceY);
	bool CheckCollisionLT(int distanceX, int distanceY);
	bool CheckCollisionRB(int distanceX, int distanceY);
	bool CheckCollisionRT(int distanceX, int distanceY);
	bool CheckCollisionLC(int distance);
	bool CheckCollisionRC(int distance);
public:
	Minion();
	~Minion();

	virtual void Update();
	virtual void Draw();

	virtual void MoveX();
	virtual void moveY();

	virtual bool UpdateMinion();
	virtual void MinionPhysics();
};

#endif
