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
public:
	Pipe();
	~Pipe();

	void CheckUse();
	void SetEvent();
};

#endif
