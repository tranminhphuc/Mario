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

	static unsigned int time;

	static Map* map;
	static bool keyA, keyD, keyS, keyW, keyShift;

	void Input();
	void InputPlayer();
	void InputMenu();
public:
	Window(unsigned int width, unsigned int heigth, string name);
	~Window();

	void Play();
	void Update();
	void Draw();

	static Map* GetMap();

	static unsigned int GetTime();
};

#endif
