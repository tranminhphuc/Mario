#pragma once

#ifndef _ANIMATION
#define _ANIMATION

#include "Textures.h"

class Animation
{
private:
	vector<Texture*> texture;
	vector<unsigned int> deltaTime;

	int currentFrame;
	int StartFrame;
	int EndFrame;

	unsigned int switchTime;
public:
	Animation(vector<string> name, vector<unsigned int> time);
	~Animation();
	void Update();
	Texture* getTexture();
	Texture* getTexture(int id);
};

#endif