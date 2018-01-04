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

void Text::Draw(sf::RenderWindow& window, string text, float x, float y, int fontSize)
{
	this->fontSize = fontSize;
	this->text.setString(text);
	this->text.setPosition(x, y);
	window.draw(this->text);
}

void Text::Draw(sf::RenderWindow& window, string text, float x, float y, int r, int g, int b, int fontSize)
{
	this->fontSize = fontSize;
	this->text.setString(text);
	this->text.setFillColor(sf::Color(r, g, b));
	this->text.setPosition(x, y);
	window.draw(this->text);
}
