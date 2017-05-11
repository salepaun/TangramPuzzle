#include "Game.h"
#include "Menu.h"


Game::Game()
	: mWindow(sf::VideoMode(WIDTH, HEIGHT), "SFML Application",sf::Style::Close)
	, mMenu(&mWindow, this)
	, mMain(&mWindow, this)
{

}

void Game::run()
{
	while (mWindow.isOpen())
	{
		if (menu)mMenu.run();
		else
			mMain.run();
	}
}




