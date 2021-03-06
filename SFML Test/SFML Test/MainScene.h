#pragma once
#include <SFML/Graphics.hpp>
#include "LineShape.h"
#include <list>
#include "Block.h"
#include <unordered_map>
#include <set>
#include "WeirdShape.h"
#include "System.h"
//#define N 7
//#define M 9
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define color(x) sf::Color(sf::Color::x)
#define EDGE 64
#define RANGE EDGE/3
#define SCORE_STRING "Score: "

class Game;

class MainScene
{
public:

	MainScene(sf::RenderWindow *window, Game *game);
	~MainScene();
	void run();

private:

	void hint();
	void correctSolution();
	void initialSolution();
	bool checkIfWon();
	void resetIsInGrid();
	void processEvents();
	void drawLines();
	void drawWeirdShapes();
	void render();
	void updateCurrent();
	bool checkCanFit(sf::Event &evnt);
	void resetCurrent();
	void centerText(sf::Text &text, std::string value, float height, sf::Color &clr = sf::Color(sf::Color::Black));
	void newLevel(int i = 1);
	void resetMatrix(std::vector<std::vector<char>>& vec);
	void setRandomPositions();
	void getHoldOfWeirdShape(int in,int x,int y);
	bool handleColorInput(sf::Color &c, int x, int y);

private:
	sf::RenderWindow *mWindow;
	sf::Texture mTexture;
	std::vector<std::vector<sf::Vector2f>> points;
	std::list<sf::LineShape> lines;
	std::vector<sf::WeirdShape> mWeirdShapes;
	std::list<sf::Color> mColors = { color(Red),color(Green),color(Blue), color(Yellow), color(Cyan),color(Magenta),sf::Color(255,165,0),sf::Color(128,0,128),sf::Color(119,136,153) };
	int mNextColorIndex = 0;
	std::vector<std::vector<char>> solution, current;
	bool hold = false;
	bool hasWon = false;
	bool quit = false;
	sf::WeirdShape *beingHold;
	sf::Vector2f dif;
	sf::Vector2f moveBy;
	sf::Text mWinText[2], mResetText, mScoreText;
	sf::Font mFont;
	Game *mGame;

};
