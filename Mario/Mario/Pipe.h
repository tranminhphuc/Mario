#pragma once

#ifndef _PIPE
#define _PIPE

#include "Library.h"

class Pipe
{
private:
	int type;
	int leftX, leftY;
	int rightX, rightY;

	int newPlayerX, newPlayerY;

	int newCurrentLevel;
	int newLevel;
	int newUnderWater;

	int delay;
	int speed;
public:
	Pipe(int type, int leftX, int leftY, int rightX, int rightY, int newPlayerX, int newPlayerY, int newCurrentLevel, int newLevel, int delay, int speed, bool newUnderWater);
	~Pipe();

	void CheckUse();
	void SetEvent();
};

#endif
