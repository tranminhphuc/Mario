#pragma once

#ifndef _WINDOW
#define _WINDOW

#include "Map.h"

class Windows
{
private:
	RenderWindow* window;
	Event event;
	Clock clock;
	static Map* map;
public:
	Windows(unsigned int width, unsigned int heigth, string name);
	~Windows();
	void Play();
	void Update(float time);
	void Draw();
	static Map* getMap();
};

#endif
