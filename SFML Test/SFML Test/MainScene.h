#pragma once
#include <SFML/Graphics.hpp>
#include "LineShape.h"
#include <list>
#include "Block.h"
#include <unordered_map>
#include "WeirdShape.h"
#define N 5
#define Color(x) sf::Color(sf::Color::x)
class Game;

class MainScene
{
public:

	MainScene(sf::RenderWindow *window, Game *game);
	~MainScene();
	void run();
private:
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void processEvents();
	void update(sf::Time);
	void drawLines();
	void render();
private:
	sf::RenderWindow *mWindow;
	sf::Texture mTexture;
	sf::Vector2f points[N + 1][N + 1];
	std::list<sf::LineShape> lines;
	sf::Block mBlock;
	std::list<sf::Color> mColors = { Color(Red),Color(Green),Color(Blue), Color(Yellow), Color(Magenta),Color(Cyan) };
	int mNextColorIndex = 0;
	std::unordered_map<std::string, sf::WeirdShape> mHash;

	Game *mGame;



};

