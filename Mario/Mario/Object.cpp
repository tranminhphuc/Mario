#include "Object.h"

Object::Object(Animation* anim, bool isCollision)
{
	animation = anim;
	collision = isCollision;
}

Object::~Object()
{
}

void Object::Draw(sf::RenderWindow & window, sf::Vector2f position)
{
	animation->getTexture()->Draw(window, position);
}

void Object::Draw(sf::RenderWindow & window, float x, float y)
{
	animation->getTexture()->Draw(window, x, y);
}

Animation* Object::GetAnimation()
{
	return animation;
}

bool Object::getCollision()
{
	return collision;
}
