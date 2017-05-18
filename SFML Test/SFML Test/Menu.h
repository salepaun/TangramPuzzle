#pragma once
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 2
#define N_STRING "N: 5 (5, 6, 7)"


class Game;

class Menu
{
public:
	Menu(sf::RenderWindow *window, Game *game);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() const;
	void run();
	void handlePlayerInput(sf::Keyboard::Key key);
	void processEvents();
	void update();
	void render() const;
	void centerText(sf::Text &text, std::string value, float height, sf::Color &clr = sf::Color(sf::Color::White));
	void setN(int num);
private:


	int selectedItemIndex;
	sf::Font mFont;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text nText;
	sf::RenderWindow *mWindow;
	sf::Sprite mBackground;
	Game *mGame;
	bool up;
	bool down;
	bool enter;

};

