#pragma once

#ifndef _MENUOPTION
#define _MENUOPTION

#include "Library.h"

class MenuOption
{
private:
	string text;
	int x, y;
public:
	MenuOption(string text, int x, int y);
	~MenuOption();

	string GetText();
	void SetText(string text);

	int GetX();
	int GetY();
};

#endif
