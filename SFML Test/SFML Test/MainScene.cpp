#include "Game.h"
#include "MainScene.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <random>
#include <complex>


MainScene::MainScene(sf::RenderWindow *window, Game *game)
	: mWindow(window)
	, mGame(game)
{
	mTexture.create(WIDTH, HEIGHT);
	for (auto i = 0; i <= N; i++)
	{
		for (auto j = 0; j <= N; j++)
		{
			points[i][j].x = EDGE + j*EDGE;
			points[i][j].y = EDGE + i*EDGE;

		}
	}
	for (auto i = 0; i <= N; i++)
	{
		for (auto j = 0; j <= N; j++)
		{
			if (j != N)
				lines.push_back(sf::LineShape(points[i][j], points[i][j + 1]));
			if (i != N )
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
	centerText(mResetText, "Press R to reset", HEIGHT - 50);
}

MainScene::~MainScene()
{
	/*for (int i = 0; i < N; i++)
	{
		delete solution[i];
		delete current[i];
	}
	delete solution;
	delete current;*/
}

void MainScene::run()
{
	while (mGame->mWindow.isOpen())
	{
		processEvents();
		//update();
		render();
	}
}

char ** MainScene::makeLevel()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, N - 1);
	std::uniform_int_distribution<> way(0, 3);


	char **m = new char*[N];


	for (auto i = 0; i < M; i++)
	{
		m[i] = new char[N];
		for (auto j = 0; j < M; j++)
			m[i][j] = 'X';
	}

	auto left = N * N;
	auto row = dist(mt);
	auto column = dist(mt);
	bool out = false;
	bool resetPosition = false;

	for (auto i = 0; i < M; i++)
	{
		if (resetPosition)
		{
			for (int it1 = 0; it1 < N; it1++)
			{
				bool found = false;
				for (int it2 = 0; it2 < N; it2++)
					if (m[it1][it2] == 'X') { row = it1; column = it2; found = true; break; }
				if (found)break;
			}
			resetPosition = false;
		}

		std::uniform_int_distribution<> randSize(1, left - M + i + 1);
		auto sz = randSize(mt);
		if (i == 0)
		{
			std::uniform_int_distribution<> d(-N / M, N / M);
			sz = left / M + d(mt);
		}
		left -= sz;
		for (int j = 0; j < sz; j++)
		{
			m[row][column] = i + '0';
			
			if (left != 0 && !(
				(row > 0 && m[row - 1][column] == 'X')
				|| (row < N - 1 && m[row + 1][column] == 'X')
				|| (column > 0 && m[row][column - 1] == 'X')
				|| (column < N - 1 && m[row][column + 1] == 'X')
				))
			{
				left += sz - j - 1;
				resetPosition = true;
				break;
			}
			else
				if (!(
					(row > 0 && m[row - 1][column] == 'X')
					|| (row < N - 1 && m[row + 1][column] == 'X')
					|| (column > 0 && m[row][column - 1] == 'X')
					|| (column < N - 1 && m[row][column + 1] == 'X')
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
					if (row < N - 1 && m[row + 1][column] == 'X')
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
					if (column < N - 1 && m[row][column + 1] == 'X')
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
	//std::cout << std::endl;
	//print(m);

	std::unordered_map<char, int> map;
	std::vector<std::pair<int, int>> x;
	for (int i = 0; i < M; i++)
	{
		char c = i + '0';
		map.insert_or_assign(c, 0);
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
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
			if (val.first < N - 1 && m[val.first + 1][val.second] != 'X' && map[m[val.first + 1][val.second]] < min)
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
			if (val.second < N - 1 && m[val.first][val.second + 1] != 'X' && map[m[val.first][val.second + 1]] < min)
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
				t.create(WIDTH, HEIGHT);
				t.update(*mWindow);
				sf::Image img = t.copyToImage();
				sf::Vector2i pos = sf::Vector2i(x, y);
				sf::Color c = img.getPixel(x, y);
				if (c == sf::Color::Red)
				{
					dif = mWeirdShapes[0].hold(sf::Vector2f(x, y));
					beingHold = &mWeirdShapes[0];
				}
				else if (c == sf::Color::Green)
				{
					dif = mWeirdShapes[1].hold(sf::Vector2f(x, y));
					beingHold = &mWeirdShapes[1];
					
				}
				else if (c == sf::Color::Blue)
				{
					dif = mWeirdShapes[2].hold(sf::Vector2f(x, y));
					beingHold = &mWeirdShapes[2];
				}
				else if (c == sf::Color::Yellow)
				{
					dif = mWeirdShapes[3].hold(sf::Vector2f(x, y));
					beingHold = &mWeirdShapes[3];
				}
				else if (c == sf::Color::Cyan)
				{
					dif = mWeirdShapes[4].hold(sf::Vector2f(x, y));
					beingHold = &mWeirdShapes[4];
				}
				else if (c == sf::Color::Magenta)
				{
					dif = mWeirdShapes[5].hold(sf::Vector2f(x, y));
					beingHold = &mWeirdShapes[5];
				}
				else break;
				resetCurrent();
				hold = true;

			}
			break;
		case sf::Event::MouseButtonReleased:
		{
			if (hold) {
				hold = false;
				if(this->checkCanFit(evnt)!=false)
				{
					beingHold->move(moveBy);
					hasWon = checkIfWon();
				}
				beingHold = nullptr;
				break;
			}}
		case sf::Event::MouseMoved:
			if (hold)
			{
				sf::Vector2i newpos = sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y) - (sf::Vector2i)dif;
				// TODO fix border colision 
				/*if (newpos.x < 0)sf::Mouse::setPosition(sf::Vector2i(0, newpos.y),*mWindow);
				if (newpos.x > WIDTH)sf::Mouse::setPosition(sf::Vector2i(WIDTH, newpos.y), *mWindow);
				if (newpos.y < 0)sf::Mouse::setPosition(sf::Vector2i(newpos.x, 0), *mWindow);
				if (newpos.y > HEIGHT)sf::Mouse::setPosition(sf::Vector2i(newpos.x,HEIGHT), *mWindow);*/
				/*if (newpos.x >= 0 && newpos.x <= WIDTH && newpos.y >= 0 && newpos.y <= HEIGHT)
					beingHold->setPosition(newpos.x, newpos.y);
				else if (newpos.x >= 0 && newpos.x <= WIDTH)
					beingHold->setPosition(newpos.x, evnt.mouseMove.y);
				if (newpos.y >= 0 && newpos.y <= HEIGHT)
					beingHold->setPosition(evnt.mouseMove.x,newpos.y);*/
				beingHold->setPosition(newpos.x, newpos.y);
			}
			break;
		case sf::Event::KeyPressed:
			switch (evnt.key.code)
			{
			case sf::Keyboard::L:
				if (hasWon)newLevel();
				hasWon = false;
				break;
			case sf::Keyboard::R:
				newLevel(0);
			}
			break;
		}
	}

}

void MainScene::update(sf::Time deltaTime)
{/*
	sf::Vector2f movement(0.f, 0.f);
	mPlayer.move(movement * deltaTime.asSeconds());*/
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
		mWindow->draw(shape);
	}
	if(beingHold)
	mWindow->draw(*beingHold);
}

//render sprites on the screen
void MainScene::render()
{
	mWindow->clear(sf::Color(70, 130, 180));
	//mWindow->draw(mBackground);
	drawLines();
	mWindow->draw(mResetText);
	drawWeirdShapes();
	if (hasWon)
	{
		mWindow->draw(mWinText[0]);
		mWindow->draw(mWinText[1]);
	}mWindow->display();
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
	if (row >= 0 && column >= 0 && row < N && column < N)
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
		if (!(row >= 0 && column >= 0 && row < N && column < N)) return false;
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
	for (auto i = 0; i < N; i++)
		for (auto j = 0; j < N; j++)
			if (current[i][j] == c) 
				current[i][j] = 'X';
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
		solution = MainScene::makeLevel();
		current = new char*[N];
		
	}
	mWeirdShapes = std::vector<sf::WeirdShape>();
	for (auto i = 0; i < N; i++)
	{
		current[i] = new char[N];
		for (int j = 0; j < N; j++)
			current[i][j] = 'X';
	}
	for (int k = 0; k < M; k++)
	{
		sf::WeirdShape shape;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (solution[i][j] == (k + '0'))
				{
					shape.addBlock(sf::Block(sf::Vector2f(EDGE*j, EDGE*i)));
				}
			}
		mWeirdShapes.push_back(shape);
	}

	auto engine = std::default_random_engine{};
	std::shuffle(std::begin(mWeirdShapes), std::end(mWeirdShapes), engine);
	auto it = mColors.begin();
	for (int i = 0; i < M; i++)
	{

		mWeirdShapes[i].setBlockColor(*it);
		std::advance(it, 1);
	}
}

void MainScene::handlePlayerInput(sf::Keyboard::Key key,
	bool isPressed)
{

}

bool MainScene::checkIfWon()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (current[i][j] == 'X')return false;
			
		
	return true;
}

void print(char **m)
{
	for (auto i = 0; i < N; i++)
	{
		for (auto j = 0; j < N; j++)
			std::cout << m[i][j] << " ";
		std::cout << std::endl;
	}
}

