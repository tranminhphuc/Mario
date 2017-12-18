#pragma once

#ifndef _WINDOW
#define _WINDOW

#include "Map.h"

class Window
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	static Map* map;
public:
	Window(unsigned int width, unsigned int heigth, string name);
	~Window();
	void Play();
	void Update(float time);
	void Draw();
	static Map* getMap();
};

#endif
