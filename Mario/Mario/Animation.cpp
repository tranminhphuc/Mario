#include "Animation.h"

Animation::Animation(vector<string> name, vector<unsigned int> time)
{
	totalTime = 0;
	deltaTime = time;

	for (int i = 0; i < name.size(); i++)
	{
		texture.push_back(new Texture(name[i]));
	}

	currentFrame = 0;
	StartFrame = 0;
	EndFrame = (int)(texture.size());
}

Animation::~Animation()
{
	for (vector<Texture*>::iterator i = texture.begin(); i != texture.end(); i++)
	{
		delete (*i);
	}
}

void Animation::Update(unsigned int time)
{
	totalTime = time;

	if (totalTime - deltaTime[currentFrame] > switchTime)
	{
		switchTime = totalTime;
		currentFrame++;

		if (currentFrame >= EndFrame)
			currentFrame = 0;
	}
}

Texture* Animation::getTexture()
{
	return texture[currentFrame];
}

Texture* Animation::getTexture(int id)
{
	return texture[id];
}
