#pragma once
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 3


class Game;

class Menu
{
public:
	Menu(sf::RenderWindow *window, Game *game);

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() const;
	void run();
	void handlePlayerInput(sf::Keyboard::Key key);
	void processEvents();
	void update();
	void render() const;
	void centerText(sf::Text &text, std::string value, float height, sf::Color &clr = sf::Color(sf::Color::White));
private:


	int selectedItemIndex;
	sf::Font mFont;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::RenderWindow *mWindow;
	sf::Sprite mBackground;
	Game *mGame;
	bool up;
	bool down;
	bool enter;

};

