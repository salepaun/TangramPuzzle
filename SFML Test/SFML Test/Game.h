#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "MainScene.h"

#define TimePerFrame sf::seconds(1.f/60.f)
#define WIDTH 800
#define HEIGHT 800
#define N 5



class Game
{
public:

	Game();
	void run();
private:
	
public:
	sf::RenderWindow mWindow;
	Menu mMenu;
	MainScene mMain;
	bool menu = true;


	float PlayerSpeed = 100.f;

};

