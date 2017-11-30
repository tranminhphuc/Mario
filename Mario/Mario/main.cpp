#include "Map.h"

int main()
{
	RenderWindow window(sf::VideoMode(800, 480), "phuc");

	Map map;
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Right)
				{
					map.MoveMap(-10);
				}
			}
		}

		map.Update(time);
		map.SetBackGroundColor(window);
		map.DrawMap(window);
		window.display();
	}
}