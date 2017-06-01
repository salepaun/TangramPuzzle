#include "Game.h"
#include "MainScene.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <random>
#include <complex>
#include "System.h"


MainScene::MainScene(sf::RenderWindow *window, Game *game)
	: mWindow(window)
	, mGame(game)
{
	mTexture.create(System::WIDTH, System::HEIGHT);
	points = new sf::Vector2f*[System::N + 1];
	for (auto i = 0; i <= System::N; i++)
	{
		points[i] = new sf::Vector2f[System::N + 1];
		for (auto j = 0; j <= System::N; j++)
		{
			points[i][j].x = EDGE + j*EDGE;
			points[i][j].y = EDGE + i*EDGE;

		}
	}
	for (auto i = 0; i <= System::N; i++)
	{
		for (auto j = 0; j <= System::N; j++)
		{
			if (j != System::N)
				lines.push_back(sf::LineShape(points[i][j], points[i][j + 1]));
			if (i != System::N)
				lines.push_back(sf::LineShape(points[i][j], points[i + 1][j]));
		}
	}
	newLevel();
	if (!mFont.loadFromFile("neuropol x rg.ttf"))
	{
		//handle error
		std::cout << "error font" << std::endl;
		mWindow->close();
		return;
	}
	centerText(mWinText[0], "You Win!", 100);
	centerText(mWinText[1], "Press L for a new level", 200);
	centerText(mResetText, "Press R to reset", System::HEIGHT - 50);
	centerText(mScoreText, SCORE_STRING + std::to_string(System::SCORE), 15);
}

MainScene::~MainScene()
{
	print(solution);
	std::cout << std::endl;
	print(current);
	for (int i = 0; i < System::N + 1; i++)
	{

		delete[] solution[i];
		if (i < System::N)
		{
			delete[] current[i];
			delete[] points[i];
		}
	}
	delete [] solution;
	delete [] current;
	delete [] points;
	
}

void MainScene::run()
{
	while (mGame->mWindow.isOpen())
	{
		processEvents();
		//update();
		render();
		if (quit)return;
	}
}

char ** MainScene::makeLevel()
{
	char **m = new char*[System::N+2];
	if (!m)std::exit(-1);

	for (auto i = 0; i < System::M; i++)
	{
		m[i] = new char[System::N + 2];
		if (!m[i])std::exit(-1);
		for (auto j = 0; j < System::M; j++)
			m[i][j] = 'X';
	}

	initialSolution(m);
	correctSolution(m);
	return m;
}

void MainScene::processEvents()
{
	sf::Event evnt;

	while (mGame->mWindow.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			mWindow->close();
			break;
		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int x = evnt.mouseButton.x;
				int y = evnt.mouseButton.y;
				sf::Texture t;
				t.create(System::WIDTH, System::HEIGHT);
				t.update(*mWindow);
				sf::Image img = t.copyToImage();
				sf::Vector2i pos = sf::Vector2i(x, y);
				sf::Color c = img.getPixel(x, y);
				
				if (!handleColorInput(c, x, y))break;
				resetCurrent();
				hold = true;
				//print(current);
			}
			break;
		case sf::Event::MouseButtonReleased:
		{
			if (hold) {
				hold = false;
				if (this->checkCanFit(evnt) != false)
				{
					beingHold->move(moveBy);
					beingHold->setInGrid(true);
					hasWon = checkIfWon();
				}
				beingHold = nullptr;
				//print(current);
				break;
			}}
		case sf::Event::MouseMoved:
			if (hold)
			{
				sf::Vector2i newpos = sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y) - (sf::Vector2i)dif;
				beingHold->setPosition(newpos.x, newpos.y);
			}
			break;
		case sf::Event::KeyPressed:
			switch (evnt.key.code)
			{
			case sf::Keyboard::L:
				if (hasWon) 
				{
					newLevel(); 
				}
				hasWon = false;
				break;
			case sf::Keyboard::R:
				setRandomPositions(); 
				resetCurrentToEmpty();
				hasWon = false;
				break;
			case sf::Keyboard::Escape:
				quit = true;
				mGame->menu = true;
				break;
			}
			break;
		}
	}
}

void MainScene::drawLines()
{
	for(auto line: lines)
	{
		mWindow->draw(line);
	}
}

void MainScene::drawWeirdShapes()
{
	for(auto &shape:mWeirdShapes)
	{
		if(shape.isInGrid())
		mWindow->draw(shape);
	}
	for (auto &shape : mWeirdShapes)
	{
		if (!shape.isInGrid())
			mWindow->draw(shape);
	}

	if(beingHold)
	mWindow->draw(*beingHold);
}

void MainScene::render()
{
	mWindow->clear(sf::Color(70, 130, 180));
	//mWindow->draw(mBackground);
	drawLines();
	mWindow->draw(mResetText);
	mWindow->draw(mScoreText);
	drawWeirdShapes();
	if (hasWon)
	{
		mWindow->draw(mWinText[0]);
		mWindow->draw(mWinText[1]);
	}
	mWindow->display();
}

bool MainScene::checkCanFit(sf::Event &evnt)
{
	
	int x = evnt.mouseButton.x;
	int y = evnt.mouseButton.y;
	sf::Vector2f mousePosition = sf::Vector2f(x, y);
	sf::Vector2f blockPosition = beingHold->getBlockPoint(mousePosition);
	sf::Vector2i modBlock(blockPosition);
	//std::cout << (150 & ~127) << std::endl;
	modBlock.x &= ~(EDGE - 1);
	modBlock.y &= ~(EDGE - 1);
	int row = modBlock.y / EDGE - 1;
	int column = modBlock.x / EDGE - 1;
	// find closest point
	if (row >= 0 && column >= 0 && row < System::N && column < System::N)
	{

		if (std::sqrt(std::pow(points[row][column].x - blockPosition.x, 2) + std::pow(points[row][column].y - blockPosition.y, 2)) < RANGE)
		{
			moveBy = points[row][column] - (sf::Vector2f)blockPosition;
		}
		else if (std::sqrt(std::pow(points[row][column + 1].x - blockPosition.x, 2) + std::pow(points[row][column + 1].y - blockPosition.y, 2)) < RANGE)
		{
			moveBy = points[row][column + 1] - (sf::Vector2f)blockPosition;
		}
		else if (std::sqrt(std::pow(points[row + 1][column].x - blockPosition.x, 2) + std::pow(points[row + 1][column].y - blockPosition.y, 2)) < RANGE)
		{
			moveBy = points[row + 1][column] - (sf::Vector2f)blockPosition;
		}
		else if (std::sqrt(std::pow(points[row + 1][column + 1].x - blockPosition.x, 2) + std::pow(points[row + 1][column + 1].y - blockPosition.y, 2)) < RANGE)
		{
			moveBy = points[row + 1][column + 1] - (sf::Vector2f)blockPosition;
		}
		else return false;
	}
	else return false;

	for(auto &block: beingHold->getBlocks())
	{
		int row = (block.getPosition() + beingHold->getPosition() + moveBy).y/EDGE-1;
		int column = (block.getPosition() + beingHold->getPosition() + moveBy).x / EDGE - 1;
		if (!(row >= 0 && column >= 0 && row < System::N && column < System::N)) return false;
	}

	for (auto &block : beingHold->getBlocks())
	{
		int row = (block.getPosition() + beingHold->getPosition() + moveBy).y / EDGE - 1;
		int column = (block.getPosition() + beingHold->getPosition() + moveBy).x / EDGE - 1;
		if (current[row][column] != 'X') return false;
		current[row][column] = beingHold->getMark();
	}
	return true;
}

void MainScene::resetCurrent()
{
	char c = beingHold->getMark();
	for (auto i = 0; i < System::N; i++)
		for (auto j = 0; j < System::N; j++)
			if (current[i][j] == c) 
				current[i][j] = 'X';
	beingHold->setInGrid(false);
}

void MainScene::centerText(sf::Text & text, std::string value,float height, sf::Color & clr)
{
	text.setFont(mFont);
	text.setFillColor(clr);
	text.setString(value);
	//mWinText.setPosition(sf::Vector2f(WIDTH / 3, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	size_t CharacterSize = text.getCharacterSize();
	std::string String = text.getString().toAnsiString();
	bool bold = (text.getStyle() & sf::Text::Bold);
	

	sf::FloatRect rect = text.getGlobalBounds();

	rect.left = (mWindow->getSize().x / 2.0f) - (rect.width / 2.0f);
	rect.top = height;

	text.setPosition(rect.left, rect.top);
}

void MainScene::newLevel(int t)
{
	if (t)
	{
		if(solution)
		{
			for (int i = 0; i < System::N; i++)
				delete[] solution[i];
			delete[] solution;
		}
		sf::WeirdShape::next = '0';
		solution = MainScene::makeLevel();
		current = new char*[System::N+1];
		
	}
	mWeirdShapes = std::vector<sf::WeirdShape>();
	for (auto i = 0; i < System::N; i++)
	{
		current[i] = new char[System::N+1];
		for (int j = 0; j < System::N; j++)
			current[i][j] = 'X';
	}
	for (int k = 0; k < System::M; k++)
	{
		sf::WeirdShape shape;
		for (int i = 0; i < System::N; i++)
			for (int j = 0; j < System::N; j++)
			{
				if (solution[i][j] == (k + '0'))
				{
					shape.addBlock(sf::Block(sf::Vector2f(EDGE*j, EDGE*i)));
				}
			}
		mWeirdShapes.push_back(shape);
	}
	setRandomPositions();
	auto engine = std::default_random_engine{};
	std::shuffle(std::begin(mWeirdShapes), std::end(mWeirdShapes), engine);
	auto it = mColors.begin();
	for (int i = 0; i < System::M; i++)
	{

		mWeirdShapes[i].setBlockColor(*it);
		std::advance(it, 1);
	}
}

void MainScene::resetCurrentToEmpty()
{
	for (int i = 0; i < System::N; i++)
		for (int j = 0; j < System::N; j++)
			current[i][j] = 'X';
}

void MainScene::setRandomPositions()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> X(0, System::WIDTH - System::N * EDGE);
	std::uniform_int_distribution<> Y(0, System::HEIGHT - System::N * EDGE);
	int x;
	int y;
	for (auto &shape : mWeirdShapes)
	{
		x = X(mt);
		y = Y(mt);
		while (x < (System::N+1) * EDGE && y < (System::N + 1) * EDGE)
		{
			x = X(mt);
			y = Y(mt);
		}
		shape.setPosition(x, y);
	}
}

void MainScene::getHoldOfWeirdShape(int i,int x,int y)
{
	if (hasWon)
	{
		System::SCORE -= System::N - 4;
		mScoreText.setString(SCORE_STRING + std::to_string(System::SCORE));
	}
	hasWon = false;
	dif = mWeirdShapes[i].hold(sf::Vector2f(x, y));
	beingHold = &mWeirdShapes[i];
}

bool MainScene::handleColorInput(sf::Color & c, int x, int y)
{
	int k = -1;

	if (c == sf::Color::Red)
	{
		getHoldOfWeirdShape(0, x, y);
		k = 0;
	}
	else if (c == sf::Color::Green)
	{
		getHoldOfWeirdShape(1, x, y);
		k = 1;
	}
	else if (c == sf::Color::Blue)
	{
		getHoldOfWeirdShape(2, x, y);
		k = 2;
	}
	else if (c == sf::Color::Yellow)
	{
		getHoldOfWeirdShape(3, x, y);
		k = 3;
	}
	else if (c == sf::Color::Cyan)
	{
		getHoldOfWeirdShape(4, x, y);
		k = 4;
	}
	else if (c == sf::Color::Magenta)
	{
		getHoldOfWeirdShape(5, x, y);
		k = 5;
	}
	else if (c.r == 255 && c.g == 165 && c.b == 0)
	{
		getHoldOfWeirdShape(6, x, y);
		k = 6;
	}
	else if (c.r == 128 && c.g == 0 && c.b == 128)
	{
		getHoldOfWeirdShape(7, x, y);
		k = 7;
	}
	else if (c.r == 119 && c.g == 136 && c.b == 153)
	{
		getHoldOfWeirdShape(8, x, y);
		k = 8;
	}
	return k != -1;
}

void MainScene::correctSolution(char **m)
{
	std::unordered_map<char, int> map;
	std::vector<std::pair<int, int>> x;
	for (int i = 0; i < System::M; i++)
	{
		char c = i + '0';
		map.insert_or_assign(c, 0);
	}
	for (int i = 0; i < System::N; i++)
		for (int j = 0; j < System::N; j++)
			if (m[i][j] == 'X') x.push_back(std::make_pair(i, j));
			else
				map[m[i][j]]++;

	char c = '0';
	bool proba = true;
	while (proba)
	{
		proba = false;
		//print(m);
		for (auto &val : x)
		{
			bool test = false;
			int min = ~(1 << 31);
			if (val.first > 0
				&& m[val.first - 1][val.second] != 'X' && map[m[val.first - 1][val.second]] < min)
			{
				test = true;
				c = m[val.first - 1][val.second];
				min = map[m[val.first - 1][val.second]];
			}
			if (val.first < System::N - 1 && m[val.first + 1][val.second] != 'X' && map[m[val.first + 1][val.second]] < min)
			{
				test = true;
				c = m[val.first + 1][val.second];
				min = map[m[val.first + 1][val.second]];
			}
			if (val.second > 0 && m[val.first][val.second - 1] != 'X' && map[m[val.first][val.second - 1]] < min)
			{
				test = true;
				c = m[val.first][val.second - 1];
				min = map[m[val.first][val.second - 1]];
			}
			if (val.second < System::N - 1 && m[val.first][val.second + 1] != 'X' && map[m[val.first][val.second + 1]] < min)
			{
				test = true;
				c = m[val.first][val.second + 1];
				min = map[m[val.first][val.second + 1]];
			}
			if (!test)proba = true;
			m[val.first][val.second] = c;
			map[c]++;
		}
	}
}

void MainScene::initialSolution(char ** m)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, System::N - 1);
	std::uniform_int_distribution<> way(0, 3);

	auto left = System::N * System::N;
	auto row = dist(mt);
	auto column = dist(mt);
	bool out = false;
	bool resetPosition = false;

	for (auto i = 0; i < System::M; i++)
	{
		if (resetPosition)
		{
			for (int it1 = 0; it1 < System::N; it1++)
			{
				bool found = false;
				for (int it2 = 0; it2 < System::N; it2++)
					if (m[it1][it2] == 'X') { row = it1; column = it2; found = true; break; }
				if (found)break;
			}
			resetPosition = false;
		}

		std::uniform_int_distribution<> randSize(1, left - System::M + i + 1);
		auto sz = randSize(mt);
		if (i == 0)
		{
			std::uniform_int_distribution<> d(-System::N / System::M, System::N / System::M);
			sz = left / System::M + d(mt);
		}
		left -= sz;
		for (int j = 0; j < sz; j++)
		{
			m[row][column] = i + '0';

			if (left != 0 && !(
				(row > 0 && m[row - 1][column] == 'X')
				|| (row < System::N - 1 && m[row + 1][column] == 'X')
				|| (column > 0 && m[row][column - 1] == 'X')
				|| (column < System::N - 1 && m[row][column + 1] == 'X')
				))
			{
				left += sz - j - 1;
				resetPosition = true;
				break;
			}
			else
				if (!(
					(row > 0 && m[row - 1][column] == 'X')
					|| (row < System::N - 1 && m[row + 1][column] == 'X')
					|| (column > 0 && m[row][column - 1] == 'X')
					|| (column < System::N - 1 && m[row][column + 1] == 'X')
					))
				{
					break;
				}
			while (1)
			{

				switch (way(mt))
				{
				case UP:
					if (row > 0 && m[row - 1][column] == 'X')
					{
						row--;
						out = true;
					}
					break;
				case DOWN:
					if (row < System::N - 1 && m[row + 1][column] == 'X')
					{
						row++;
						out = true;
					}
					break;
				case LEFT:
					if (column > 0 && m[row][column - 1] == 'X')
					{
						column--;
						out = true;
					}
					break;
				case RIGHT:
					if (column < System::N - 1 && m[row][column + 1] == 'X')
					{
						column++;
						out = true;
					}
					break;
				}
				if (out) {
					out = false;
					break;
				}
			}
		}
	}
}

bool MainScene::checkIfWon()
{
	for (int i = 0; i < System::N; i++)
		for (int j = 0; j < System::N; j++)
			if (current[i][j] == 'X')return false;
			
	System::SCORE += System::N - 4;
	mScoreText.setString(SCORE_STRING + std::to_string(System::SCORE));
	return true;
}

void print(char **m)
{
	printf("\n\n");
	for (auto i = 0; i < System::N; i++)
	{
		for (auto j = 0; j < System::N; j++)
			std::cout << m[i][j] << " ";
		std::cout << std::endl;
	}
}

