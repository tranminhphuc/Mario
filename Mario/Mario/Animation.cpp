#include "Animation.h"

Animation::Animation(vector<string> name, vector<float> time)
{
	totalTime = 0;
	deltaTime = time;

	for (int i = 0; i < name.size(); i++)
	{
		texture.push_back(new Textures(name[i]));
	}

	currentFrame = 0;
	StartFrame = 0;
	EndFrame = (int)(texture.size());
}

Animation::~Animation()
{
	for (vector<Textures*>::iterator i = texture.begin(); i != texture.end(); i++)
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

void Animation::Draw(sf::RenderWindow& window, Vector2f position)
{
	texture[currentFrame]->Draw(window, position);
}

void Animation::Draw(sf::RenderWindow & window, float x, float y)
{
	texture[currentFrame]->Draw(window, x, y);
}
