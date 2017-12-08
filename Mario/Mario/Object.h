#pragma once

#ifndef _OBJECT
#define _OBJECT

#include "Animation.h"

class Object
{
private:
	Animation* animation;
	bool collision;
public:
	Object(Animation* anim, bool isCollision);
	~Object();
	void Draw(sf::RenderWindow& window, Vector2f position);
	void Draw(sf::RenderWindow& window, float x, float y);
	Animation* GetAnimation();
	bool getCollision();
};

#endif
