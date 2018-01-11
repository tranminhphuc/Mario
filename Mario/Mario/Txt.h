#pragma once

#ifndef _TEXT
#define _TEXT

#include "Library.h"
#include "Textures.h"

class Text
{
private:
	Texture* font;

	sf::IntRect crop;
	sf::RectangleShape rect;

	int fontSize;
	int extraLeft, nextExtraLeft;

	int GetPos(int text);
	void CheckExtra(int text);
public:
	Text();
	~Text();
	
	void Draw(sf::RenderWindow& window, string text, float x, float y, int fontSize = 16);
	void Draw(sf::RenderWindow& window, string text, float x, float y, int r, int g, int b, int fontSize = 16);

	void SetFont(string file);
	int GetTextWidth(std::string text, int fontSize = 16);
};

#endif
