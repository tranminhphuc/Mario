#pragma once

#ifndef _OBJECT
#define _OBJECT

#include "Animation.h"

class Object
{
private:
	Animation* animation;
	bool collision;
	bool canDestroy;
	bool visible;
public:
	Object(Animation* anim, bool collision, bool canDestroy, bool visible);
	~Object();
	void Draw(sf::RenderWindow& window, sf::Vector2f position);
	void Draw(sf::RenderWindow& window, float x, float y);
	Animation* GetAnimation();
	bool GetCollision();
	bool GetCanDestroy();
	bool GetVisible();
};

#endif
