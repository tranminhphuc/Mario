#include "Txt.h"

Text::Text()
{
	fontSize = 16;
}

Text::~Text()
{
	
}

void Text::SetFont(string file)
{
	font.loadFromFile(file);
	text.setFont(font);
}

void Text::Draw(sf::RenderWindow & window, string text, int fontSize, float x, float y)
{
	this->fontSize = fontSize;
	this->text.setString(text);
	this->text.setPosition(x, y);
	window.draw(this->text);
}
