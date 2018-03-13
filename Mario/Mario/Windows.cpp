#include "Windows.h"
//#include "Game.h"

Map* Window::map;
bool Window::movePressed = false;
bool Window::keyMenuPressed = false;
bool Window::left = false;
bool Window::right = false;
bool Window::down = false;
bool Window::up = false;
bool Window::keyShift = false;
unsigned int Window::time = 0;

int Window::gameWidth = 800;
int Window::gameHeight = 480;

int Window::keyA = 0;
int Window::keyD = 0;
int Window::keyS = 0;
int Window::keySpace = 0;

Text* Window::text = new Text();
MenuManager* Window::menuManager = new MenuManager();

Window::Window(unsigned int width, unsigned int heigth, string name)
{
	window = new sf::RenderWindow(sf::VideoMode(width, heigth), name);
	map = new Map();

	window->setFramerateLimit(30);

	Window::keyA = sf::Keyboard::Left;
	Window::keyD = sf::Keyboard::Right;
	Window::keyS = sf::Keyboard::Down;
	Window::keySpace = sf::Keyboard::Space;
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

			Input();
		}

		Update();
		Draw();
		window->display();
	}
}

void Window::Update()
{
	Window::GetMenuManager()->Update();
}

void Window::Draw()
{
	Window::GetMenuManager()->Draw(*window);
}

Map* Window::GetMap()
{
	return map;
}

unsigned int Window::GetTime()
{
	return time;
}

Text * Window::GetText()
{
	return text;
}

MenuManager * Window::GetMenuManager()
{
	return menuManager;
}

string Window::GetKeyString(int keyID)
{
	if (keyID >= 97 && keyID <= 122)
		return string(1, '0' + (keyID - 32) - 48);

	if (keyID >= 48 && keyID <= 57)
		return string(1, '0' + (keyID - 32) - 48);

	switch (keyID)
	{
	case sf::Keyboard::Escape:
		return "ESCAPE";
	case sf::Keyboard::Space:
		return "SPACE";
	case sf::Keyboard::LShift:
		return "LSHIFT";
	case sf::Keyboard::RShift:
		return "RSHIFT";
	case sf::Keyboard::Up:
		return "UP";
	case sf::Keyboard::Down:
		return "DOWN";
	case sf::Keyboard::Left:
		return "LEFT";
	case sf::Keyboard::Right:
		return "RIGHT";
	case sf::Keyboard::LControl:
		return "LCONTROl";
	case sf::Keyboard::RControl:
		return "RCONTROL";
	}

	return "NONE";
}

void Window::ResetKeys()
{
	keyMenuPressed = left = right = up = down = Window::keySpace = keyShift = false;
}

void Window::Input()
{
	switch (Window::GetMenuManager()->GetView())
	{
	case 1:
		InputPlayer();
		break;
	default:
		InputMenu();
		break;
	}
}

void Window::InputPlayer()
{
	if(event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == Window::keyA)
		{
			left = true;
		}

		if (event.key.code == Window::keyD)
		{
			right = true;
		}
	}

	if(event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == Window::keyA)
		{
			left = false;
		}

		if (event.key.code == Window::keyD)
		{
			right = false;
		}
	}

	if (left)
	{
		map->MoveMap(10);
	}

	if (right)
	{
		map->MoveMap(-10);
	}
}

void Window::InputMenu()
{
	if (event.type == sf::Event::KeyPressed)
	{
		Window::GetMenuManager()->SetKey(event.key.code);

		switch (event.key.code)
		{
		case sf::Keyboard::S: case sf::Keyboard::Down:
			if (!keyMenuPressed)
			{
				Window::GetMenuManager()->keyPressed(Down);
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::W : case sf::Keyboard::Up:
			if (!keyMenuPressed)
			{
				Window::GetMenuManager()->keyPressed(Up);
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::Return:
			if (!keyMenuPressed)
			{
				Window::GetMenuManager()->Enter();
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::Escape:
			if (!keyMenuPressed)
			{
				Window::GetMenuManager()->Escape();
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::A: case sf::Keyboard::Left:
			if (!keyMenuPressed)
			{
				Window::GetMenuManager()->keyPressed(Left);
				keyMenuPressed = true;
			}
			break;
		case sf::Keyboard::D: case sf::Keyboard::Right:
			if (!keyMenuPressed)
			{
				Window::GetMenuManager()->keyPressed(Right);
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
