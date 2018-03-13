#pragma once

#ifndef _WINDOW
#define _WINDOW

#include "Map.h"
#include "MenuManager.h"
#include "Txt.h"

class Window
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;

	static unsigned int time;

	static Map* map;
	static bool movePressed, keyMenuPressed, left, right, down, up, keyShift;

	static MenuManager* menuManager;
	static Text* text;

	void Input();
	void InputPlayer();
	void InputMenu();
public:
	enum Key
	{
		Up,
		Down,
		Left,
		Right
	};

	static int gameWidth, gameHeight;
	static int keyA, keyD, keyS, keySpace;
	static bool space;

	Window(unsigned int width, unsigned int heigth, string name);
	~Window();

	void Play();
	void Update();
	void Draw();

	static Map* GetMap();

	static unsigned int GetTime();
	static void ResetKeys();

	static Text* GetText();
	static MenuManager* GetMenuManager();
	static string GetKeyString(int keyID);
};

#endif
