#include "MenuOption.h"

MenuOption::MenuOption(string text, int x, int y)
{
	this->text = text;
	this->x = x;
	this->y = y;
}

MenuOption::~MenuOption()
{
}

string MenuOption::GetText()
{
	return text;
}

void MenuOption::SetText(string text)
{
	this->text = text;
}

int MenuOption::GetX()
{
	return x;
}

int MenuOption::GetY()
{
	return y;
}
