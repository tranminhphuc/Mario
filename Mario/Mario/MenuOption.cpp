#include "MenuOption.h"

MenuOption::MenuOption(string text, float X, float Y)
{
	this->text = text;
	this->x = X;
	this->y = Y;
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
