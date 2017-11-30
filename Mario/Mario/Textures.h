#pragma once

#ifndef _TEXTURES
#define _TEXTURES

#include "Library.h"

class Textures
{
private:
	Texture* texture;
	RectangleShape rect;
public:
	Textures(String name);
	void SetSize(float x, float y);
	void SetSize(Vector2f size);
	void SetPosition(float x, float y);
	void SetPosition(Vector2f position);
	void SetRect(Texture* texture);
	void Draw(RenderWindow& window, Vector2f position);
	void Draw(RenderWindow& window, float x, float y);
};

#endif
