#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <windows.h>



int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	Game game;
	game.run();

	return 0;
}