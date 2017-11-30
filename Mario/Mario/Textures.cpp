#include "Textures.h"

Textures::Textures(String name)
{
	texture = new Texture();
	texture->loadFromFile(name);
	rect.setTexture(texture);

	SetSize((float)texture->getSize().x, (float)texture->getSize().y);
}

void Textures::SetSize(float x, float y)
{
	rect.setSize(Vector2f(x, y));
}

void Textures::SetSize(Vector2f size)
{
	rect.setSize(size);
}

void Textures::SetPosition(float x, float y)
{
	rect.setPosition(Vector2f(x, y));
}

void Textures::SetPosition(Vector2f position)
{
	rect.setPosition(position);
}

void Textures::SetRect(Texture* texture)
{
	rect.setTexture(texture);
}

void Textures::Draw(RenderWindow& window, Vector2f position)
{
	SetPosition(position);
	window.draw(rect);
}

void Textures::Draw(RenderWindow & window, float x, float y)
{
	SetPosition(x, y);
	window.draw(rect);
}
