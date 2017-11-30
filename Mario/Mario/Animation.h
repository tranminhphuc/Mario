#pragma once

#ifndef _ANIMATION
#define _ANIMATION

#include "Textures.h"

class Animation
{
private:
	vector<Textures*> texture;
	vector<float> deltaTime;

	int currentFrame;
	int StartFrame;
	int EndFrame;

	float totalTime;
	float switchTime;
public:
	Animation(vector<string> name, vector<float> time);
	~Animation();
	void Update(float time);
	void Draw(sf::RenderWindow& window, Vector2f position);
	void Draw(sf::RenderWindow& window, float x, float y);
};

#endif