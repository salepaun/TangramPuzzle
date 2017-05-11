#include "Menu.h"
#include "Game.h"
#include <iostream>

#define PLAY 0
#define OPTIONS 1
#define EXIT 2

Menu::Menu(sf::RenderWindow* window, Game *game)
{
	mGame = game;
	mWindow = window;
	if (!font.loadFromFile("neuropol x rg.ttf"))
	{
		//handle error
		std::cout << "error font" << std::endl;
		mWindow->close();
		return;
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(WIDTH / 3, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(WIDTH / 3, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(WIDTH / 3, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;

	up = down = enter = false;
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	up = false;
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	down = false;
}

int Menu::GetPressedItem() const
{
	return selectedItemIndex;
}

void Menu::run()
{
	while (mGame->mWindow.isOpen())
	{
		processEvents();
		update();
		render();
		if (!mGame->menu)return;
	}
}

void Menu::handlePlayerInput(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Up || key == sf::Keyboard::W)
		up = true;
	else if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
		down = true;
	else if (key == sf::Keyboard::Return)
		enter = true;
}

void Menu::processEvents()
{
	sf::Event evnt;
	while (mWindow->pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(evnt.key.code);
			break;
		case sf::Event::Closed:
			mGame->mWindow.close();
			break;
		}

	}
}

void Menu::update()
{
	if (up) MoveUp();
	else if (down) MoveDown();
	else if (enter)
	{
		mGame->menu = false;
		switch (GetPressedItem())
		{
		case PLAY:

			break;
		case OPTIONS:
			break;
		case EXIT:
			mWindow->close();
			break;
		}
	}
}

void Menu::render() const
{
	mWindow->clear();
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		mWindow->draw(menu[i]);
	}

	mWindow->display();
}
