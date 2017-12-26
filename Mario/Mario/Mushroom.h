#pragma once

#ifndef _MUSHROOM
#define _MUSHROOM

#include "Minion.h"

class Mushroom : public Minion
{
private:
	int x, y;
	bool powerUp;
public:
	Mushroom();
	~Mushroom();
};

#endif
