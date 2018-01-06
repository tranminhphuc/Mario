#pragma once

#ifndef _EVENT
#define _EVENT

class Event
{
public:
	unsigned int time;
	int delay;
	int speed;

	bool endGame;

	Event();
	~Event();
};

#endif
