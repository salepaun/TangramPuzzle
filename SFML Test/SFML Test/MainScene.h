#pragma once
#include <SFML/Graphics.hpp>
#include "LineShape.h"
#include <list>
#include "Block.h"
#include <unordered_map>
#include <set>
#include "WeirdShape.h"
#define N 5
#define M 6
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
	bool checkIfWon();
	void processEvents();
	void update(sf::Time);
	void drawLines();
	void drawWeirdShapes();
	void render();
	bool checkCanFit(sf::Event &evnt);
	void resetCurrent();
	void centerText(sf::Text &text, std::string value, float height, sf::Color &clr = sf::Color(sf::Color::Black));
	void newLevel(int i = 1);


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
	bool hasWon = false;
	sf::WeirdShape *beingHold;
	sf::Vector2f dif;
	sf::Vector2f moveBy;
	sf::Text mWinText[2], mResetText;
	sf::Font mFont;
	
	


	Game *mGame;



};

void print(char**);