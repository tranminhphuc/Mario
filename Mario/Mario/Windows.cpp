#include "Windows.h"
#include "Game.h"

Map* Window::map;
bool Window::keyA = false;
bool Window::keyD = false;
bool Window::keyS = false;
bool Window::keyW = false;
bool Window::keyShift = false;
unsigned int Window::time = 0;

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
		time = clock.getElapsedTime().asMilliseconds();

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

		Update();
		Draw();
		window->display();
	}
	
}

void Window::Update()
{
	map->Update();
}

void Window::Draw()
{
	map->SetBackGroundColor(*window);
	map->Draw(*window);
}

Map* Window::GetMap()
{
	return map;
}

unsigned int Window::GetTime()
{
	return time;
}

void Window::Input()
{

}

void Window::InputPlayer()
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == Game::keyD)
		{
			keyD = true;
		}

		if (event.key.code == Game::keyS)
		{
			keyS = true;

			if (!map->GetUnderWater())
				map->GetPlayer()->SetSquat(true);
		}

		if (event.key.code == Game::keyA)
		{
			keyA = true;
		}

		if (event.key.code == Game::keySpace)
		{
			if (!Game::keySpace)
			{
				//map->GetPlayer()->j
			}
		}

		if (event.key.code == Game::keyShift)
		{
			if (!keyShift)
			{
				map->GetPlayer()->StartMove();
				keyShift = true;
			}
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == Game::keyD)
		{
			keyD = false;
		}

		if (event.key.code == Game::keyS)
		{
			keyS = false;
		}

		if (event.key.code == Game::keyA)
		{
			keyA = false;
		}

		if (event.key.code == Game::keySpace)
		{
			Game::keySpace = false;
		}

		if (event.key.code == Game::keyShift)
		{
			if (keyShift)
			{
				map->GetPlayer()->ResetMove();
				keyShift = false;
			}
		}
	}
}

void Window::InputMenu()
{
}
