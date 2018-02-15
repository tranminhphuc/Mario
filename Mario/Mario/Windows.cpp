#include "Windows.h"
#include "Game.h"

Map* Window::map;
bool Window::movePressed = false;
bool Window::keyMenuPressed = false;
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

			//InputMenu();
		}

		//Update();
		Draw();
		window->display();
	}
	
}

void Window::Update()
{
	Game::GetMenuManager()->Update();
}

void Window::Draw()
{
	Game::GetMenuManager()->Draw(*window);
}

Map* Window::GetMap()
{
	return map;
}

unsigned int Window::GetTime()
{
	return time;
}

void Window::ResetKeys()
{
	keyMenuPressed = keyA = keyD = keyW = keyS = Game::keySpace = keyShift = false;
}

void Window::Input()
{
}

void Window::InputPlayer()
{
}

void Window::InputMenu()
{
	if (event.type == sf::Event::KeyPressed)
	{
		Game::GetMenuManager()->SetKey(event.key.code);

		switch (event.key.code)
		{
		case sf::Keyboard::S: case sf::Keyboard::Down:
			if (!keyMenuPressed)
			{
				Game::GetMenuManager()->keyPressed(Down);
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::W : case sf::Keyboard::Up:
			if (!keyMenuPressed)
			{
				Game::GetMenuManager()->keyPressed(Up);
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::Return:
			if (!keyMenuPressed)
			{
				Game::GetMenuManager()->Enter();
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::Escape:
			if (!keyMenuPressed)
			{
				Game::GetMenuManager()->Escape();
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::A: case sf::Keyboard::Left:
			if (!keyMenuPressed)
			{
				Game::GetMenuManager()->keyPressed(Left);
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::D: case sf::Keyboard::Right:
			if (!keyMenuPressed)
			{
				Game::GetMenuManager()->keyPressed(Right);
				keyMenuPressed = true;
			}
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::A: case sf::Keyboard::D: case sf::Keyboard::W: case sf::Keyboard::S: case sf::Keyboard::Left: case sf::Keyboard::Right: case sf::Keyboard::Up: case sf::Keyboard::Down: case sf::Keyboard::Return: case sf::Keyboard::Escape:
			keyMenuPressed = false;
			break;
		default:
			break;
		}
	}
}
