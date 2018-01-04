#pragma once

#ifndef _MENUOPTION
#define _MENUOPTION

#include "Library.h"

class MenuOption
{
private:
	string text;
	float x, y;
public:
	MenuOption(string text, float x, float y);
	~MenuOption();

	string GetText();
	void SetText(string text);

	float GetX();
	float GetY();
};

#endif
