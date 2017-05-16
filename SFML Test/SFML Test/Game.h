#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "MainScene.h"

//#define WIDTH 1200
//#define HEIGHT 800
#define MENU 0
#define MAIN 1


class Game
{
public:

	Game();
	void run();
private:
	
public:
	sf::RenderWindow mWindow;
	Menu *mMenu;
	MainScene *mMain;
	bool menu = true;

};

