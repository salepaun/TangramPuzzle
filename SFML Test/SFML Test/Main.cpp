#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"


#define N

int main()
{
	Game game;
	game.run();

	return 0;
}

/*
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Close);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::Vector2i diff;
	bool hold = false;
	sf::Color q = sf::Color::Green;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					std::cout << "mousle clicked" << std::endl;
					int x = event.mouseButton.x;
					int y = event.mouseButton.y;
					sf::Texture t;
					t.create(800, 800);
					t.update(window);
					sf::Image img = t.copyToImage();
					sf::Vector2i pos = sf::Vector2i(x, y);
					std::cout << "mouse " << x << "," << y << std::endl;
					sf::Color c = img.getPixel(x, y);
					if (c == sf::Color::Green)
					{
						std::cout << "green" << std::endl;
						diff = pos - (sf::Vector2i)shape.getPosition();
						hold = true;
					}
				}
				break;
			case sf::Event::MouseButtonReleased:
				hold = false;
				break;
			case sf::Event::MouseMoved:
				if (hold)
				{
					sf::Vector2i newpos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y) - (sf::Vector2i)diff;
					shape.setPosition(newpos.x, newpos.y);
				}
			}

		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
*/