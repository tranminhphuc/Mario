#include "Txt.h"
#include "Windows.h"
//#include "Game.h"

Text::Text()
{
	crop.left = 0;
	crop.top = 0;
	crop.width = 8;
	crop.height = 8;

	rect.setPosition(0, 0);
	rect.setSize(sf::Vector2f(16, 16));

	fontSize = 16;
	extraLeft = 0;
	nextExtraLeft = 0;
}

Text::~Text()
{
	delete font;
}

void Text::Draw(sf::RenderWindow& window, string text, float x, float y, int fontSize)
{
	this->fontSize = fontSize;
	
	this->extraLeft = 0;
	this->nextExtraLeft = 0;

	for (int i = 0; i < text.size(); i++)
	{
		crop.left = GetPos(text.at(i));
		rect.setPosition(x + fontSize * i - extraLeft, y);
		rect.setSize(sf::Vector2f((float)fontSize, (float)fontSize));
		
		font->Draw(window, rect.getPosition(), rect.getSize(), crop);
		extraLeft += nextExtraLeft;
		nextExtraLeft = 0;
	}
}

void Text::Draw(sf::RenderWindow& window, string text, float x, float y, int r, int g, int b, int fontSize)
{
	this->fontSize = fontSize;
	this->extraLeft = 0;
	this->nextExtraLeft = 0;

	for (int i = 0; i < text.size(); i++)
	{
		rect.setFillColor(sf::Color(r, g, b));
		crop.left = GetPos(text.at(i));

		rect.setPosition(x + fontSize * i - extraLeft, y);
		rect.setSize(sf::Vector2f((float)fontSize, (float)fontSize));

		font->Draw(window, rect.getPosition(), rect.getSize(), crop);
		extraLeft += nextExtraLeft;
		nextExtraLeft = 0;
		rect.setFillColor(sf::Color(255, 255, 255));
	}
}

void Text::DrawCenterX(sf::RenderWindow& window, string text, float y, int r, int g, int b, int fontsize)
{
	float x = Window::gameWidth / 2.0f - GetTextWidth(text, fontSize) / 2.0f;
	Draw(window, text, x, y, r, g, b, fontSize);
}

void Text::SetFont(string file)
{
	font = new Texture(file);
}

int Text::GetTextWidth(std::string text, int fontSize)
{
	int output = (int)text.size() * fontSize;
	nextExtraLeft = 0;

	for (int i = 0; i < text.size(); i++)
	{
		CheckExtra(text.at(i));
	}

	output -= nextExtraLeft;
	return output;
}

int Text::GetPos(int text)
{
	if (text >= 43 && text < 91)
	{
		CheckExtra(text);
		return (text - 43) * crop.width + crop.width;
	}

	if (text >= 118 && text < 123)
	{
		return (text - 70) * crop.width + crop.width;
	}

	return 0;
}

void Text::CheckExtra(int text)
{
	switch (text)
	{
	case 44: case 46: case 58: case 59:
		nextExtraLeft += 4 * fontSize / (int)rect.getSize().x;
		break;
	default:
		break;
	}
}
