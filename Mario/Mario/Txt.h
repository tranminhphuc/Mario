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
	void Draw(sf::RenderWindow& window, string text, float x, float y, int fontSize = 16);
	void Draw(sf::RenderWindow& window, string text, float x, float y, int r, int g, int b, int fontSize = 16);
};

#endif
