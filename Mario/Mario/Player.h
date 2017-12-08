#pragma once

#ifndef _PLAYER
#define _PLAYER

#include "Animation.h"

class Player
{
private:
	Animation* mario;
	float x, y;
	float width, height;

	bool CollisionLB();
	bool CollisionLT();
	bool CollisionRB();
	bool CollisionRT();
	bool CollisionLC();
	bool CollisionRC();
public:
	Player();
	~Player();
};

#endif
