#include "MenuOption.h"

MenuOption::MenuOption(string text, float x, float y)
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

float MenuOption::GetX()
{
	return x;
}

float MenuOption::GetY()
{
	return y;
}
