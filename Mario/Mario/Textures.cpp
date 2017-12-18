#include "Textures.h"

Texture::Texture(string name)
{
	texturess = new sf::Texture();
	texturess->loadFromFile(name);
	rect.setTexture(texturess);

	SetSize((float)texturess->getSize().x, (float)texturess->getSize().y);
}

void Texture::SetSize(float x, float y)
{
	rect.setSize(sf::Vector2f(x, y));
}

void Texture::SetSize(sf::Vector2f size)
{
	rect.setSize(size);
}

void Texture::SetPosition(float x, float y)
{
	rect.setPosition(sf::Vector2f(x, y));
}

void Texture::SetPosition(sf::Vector2f position)
{
	rect.setPosition(position);
}

void Texture::SetRect(sf::Texture* textures)
{
	rect.setTexture(textures);
}

void Texture::Draw(sf::RenderWindow& window, sf::Vector2f position)
{
	SetPosition(position);
	window.draw(rect);
}

void Texture::Draw(sf::RenderWindow & window, float x, float y)
{
	SetPosition(x, y);
	window.draw(rect);
}
