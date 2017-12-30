#pragma once

#ifndef _TEXT
#define _TEXT

#include "Library.h"

class Text
{
private:
	sf::Text text;
	sf::Font font;

	int fontSize;
public:
	Text();
	~Text();
	void SetFont(string file);
	void Draw(sf::RenderWindow& window, string text, int fontSize, float x, float y);
};

#endif
