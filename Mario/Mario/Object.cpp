#include "Object.h"

Object::Object(Animation* animation, bool collision, bool canDestroy, bool visible)
{
	this->animation = animation;
	this->collision = collision;
	this->canDestroy = canDestroy;
	this->visible = visible;
}

Object::~Object()
{
}

void Object::Draw(sf::RenderWindow & window, sf::Vector2f position)
{
	animation->getTexture()->Draw(window, position);
}

Animation* Object::GetAnimation()
{
	return animation;
}

bool Object::GetCollision()
{
	return collision;
}

bool Object::GetCanDestroy()
{
	return canDestroy;
}

bool Object::GetVisible()
{
	return visible;
}
