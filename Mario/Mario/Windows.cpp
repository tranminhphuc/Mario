#include "Windows.h"

Map* Window::map;

Window::Window(unsigned int width, unsigned int heigth, string name)
{
	window = new sf::RenderWindow(sf::VideoMode(width, heigth), name);
	map = new Map();
}

Window::~Window()
{
	delete window;
}

void Window::Play()
{
	while (window->isOpen())
	{
		float time = clock.restart().asSeconds();

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Right)
				{
					map->MoveMap(-50);
				}
			}
		}

		Update(time);
		Draw();
		window->display();
	}
	
}

void Window::Update(float time)
{
	map->Update(time);
}

void Window::Draw()
{
	map->SetBackGroundColor(*window);
	map->DrawMap(*window);
}

Map* Window::getMap()
{
	return map;
}
