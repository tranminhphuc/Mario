#include "Textures.h"

Texture::Texture(string name)
{
	sf::Image image;
	image.loadFromFile(name);
	image.createMaskFromColor(sf::Color(255, 0, 255, 255));

	textures = new sf::Texture();
	textures->loadFromImage(image);
	rect.setTexture(textures);

	SetSize((float)textures->getSize().x, (float)textures->getSize().y);
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
	rect.setPosition(position);
	window.draw(rect);
}

void Texture::Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::IntRect IMGRect)
{
	rect.setTextureRect(IMGRect);
	rect.setSize(size);
	rect.setPosition(position);
	window.draw(rect);
}
