#pragma once
#include <SFML/Graphics.hpp>
#include "LineShape.h"
#include <list>
#include "Block.h"
#include <unordered_map>
#include "WeirdShape.h"
#define N 5
#define M 5
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define color(x) sf::Color(sf::Color::x)
#define EDGE 64
#define RANGE EDGE/3

class Game;

class MainScene
{
public:

	MainScene(sf::RenderWindow *window, Game *game);
	~MainScene();
	void run();
	static char **makeLevel();
private:
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void processEvents();
	void update(sf::Time);
	void drawLines();
	void drawWeirdShapes();
	void render();
	bool checkCanFit(sf::Event &evnt);
private:
	sf::RenderWindow *mWindow;
	sf::Texture mTexture;
	sf::Vector2f points[N + 1][N + 1];
	std::list<sf::LineShape> lines;
	std::vector<sf::WeirdShape> mWeirdShapes;
	std::list<sf::Color> mColors = { color(Red),color(Green),color(Blue), color(Yellow), color(Cyan),color(Magenta) };
	int mNextColorIndex = 0;
	std::unordered_map<std::string, sf::WeirdShape> mHash;
	char **solution, **current;
	bool hold = false;
	sf::WeirdShape *beingHold;
	sf::Vector2f dif;
	sf::Vector2f moveBy;


	Game *mGame;



};

void print(char**);