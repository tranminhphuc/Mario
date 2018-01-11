#pragma once

#ifndef _TEXTURES
#define _TEXTURES

#include "Library.h"

class Texture
{
private:
	sf::Texture* textures;
	sf::RectangleShape rect;
public:
	Texture(string name);
	void SetSize(float x, float y);
	void SetSize(sf::Vector2f size);
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f position);
	void SetRect(sf::Texture* textures);
	void Draw(sf::RenderWindow& window, sf::Vector2f position);
	void Draw(sf::RenderWindow& window, float x, float y);
	void Draw(sf::RenderWindow& window, sf::Vector2f position, sf::IntRect IMGRect);
};

#endif
