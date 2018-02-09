#pragma once

#ifndef _GAME
#define _GAME

#include "Library.h"
#include "Txt.h"
#include "MenuManager.h"

class Game
{
private:
	static MenuManager* menuManager;
	static Text* text;
public:
	static int gameWidth, gameHeight;
	static int keyA, keyD, keyS, keySpace, keyShift;
	static bool space;

	Game();
	~Game();

	static Text* GetText();
	static MenuManager* GetMenuManager();
	static string GetKeyString(int keyID);
};

#endif
