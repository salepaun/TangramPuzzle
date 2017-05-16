#include "Game.h"
#include "Menu.h"
#include "System.h"


Game::Game()
	: mWindow(sf::VideoMode(System::WIDTH, System::HEIGHT), "Tangram Puzzle",sf::Style::Close)
	, mMenu(nullptr)
	, mMain(nullptr)
{
}

void Game::run()
{
	while (mWindow.isOpen())
	{
		if (menu)
		{
			mMenu = new Menu(&mWindow, this);
			mMenu->run();
			delete mMenu;
			mMenu = nullptr;
		}
		else
		{
			mMain = new MainScene(&mWindow, this);
			mMain->run();
			delete mMain;
			mMain = nullptr;
		}
	}
}




