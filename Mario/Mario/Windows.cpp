#include "Windows.h"

Map* Windows::map;

Windows::Windows(unsigned int width, unsigned int heigth, string name)
{
	window = new RenderWindow(VideoMode(width, heigth), name);
	map = new Map();
}

Windows::~Windows()
{
	delete window;
}

void Windows::Play()
{
	while (window->isOpen())
	{
		float time = clock.restart().asSeconds();

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Right)
				{
					map->MoveMap(-10);
				}
			}
		}

		Update(time);
		Draw();
		window->display();
	}
	
}

void Windows::Update(float time)
{
	map->Update(time);
}

void Windows::Draw()
{
	map->SetBackGroundColor(*window);
	map->DrawMap(*window);
}

Map* Windows::getMap()
{
	return map;
}
