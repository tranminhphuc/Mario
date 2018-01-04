#include "Windows.h"
#include "Game.h"

Map* Window::map;
bool Window::keyA = false;
bool Window::keyD = false;
bool Window::keyS = false;
bool Window::keyW = false;

Window::Window(unsigned int width, unsigned int heigth, string name)
{
	window = new sf::RenderWindow(sf::VideoMode(width, heigth), name);
	map = new Map();

	Game::keyA = sf::Keyboard::A;
	Game::keyD = sf::Keyboard::D;
	Game::keyS = sf::Keyboard::S;
	Game::keySpace = sf::Keyboard::Space;
	Game::keyShift = sf::Keyboard::LShift;
}

Window::~Window()
{
	delete window;
}

void Window::Play()
{
	while (window->isOpen())
	{
		unsigned int time = clock.getElapsedTime().asMilliseconds();

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

void Window::Update(unsigned int time)
{
	map->UpdateBlock(time);
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
