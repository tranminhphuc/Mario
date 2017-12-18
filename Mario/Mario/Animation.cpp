#include "Animation.h"

Animation::Animation(vector<string> name, vector<float> time)
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

void Animation::Update(float time)
{
	totalTime += time;

	if (totalTime >= deltaTime[currentFrame])
	{
		totalTime -= deltaTime[currentFrame];
		currentFrame++;

		if (currentFrame >= EndFrame)
		{
			currentFrame = 0;
		}
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
