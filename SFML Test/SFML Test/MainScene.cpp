#include "Game.h"
#include "MainScene.h"


MainScene::MainScene(sf::RenderWindow *window, Game *game)
	: mWindow(window)
	, mGame(game)
	, mBlock(sf::Color(sf::Color::Red), sf::Vector2f(100, 100))
{
	mTexture.create(WIDTH, HEIGHT);

	for (auto i = 0; i < N; i++)
	{
		for (auto j = 0; j < N; j++)
		{

			points[i][j].x = WIDTH / (N + 2) + i*WIDTH / (N + 2);
			points[i][j].y = HEIGHT / (N + 2) + j*HEIGHT / (N + 2);
		}
	}

	for (auto i = 0; i < N; i++)
	{
		for (auto j = 0; j < N; j++)
		{
			if(j!=N-1)
			lines.push_back(sf::LineShape(points[i][j], points[i][j + 1]));
			if(i!=N-1)
			lines.push_back(sf::LineShape(points[i][j], points[i+1][j]));
		}
	}


	//mPlayer.setTexture(mTexture);
	//mPlayer.setPosition(100.f, 100.f);


	//izracunaj kombinaciju
}

MainScene::~MainScene()
{
	
}

void MainScene::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mGame->mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void MainScene::processEvents()
{
	sf::Event evnt;
	while (mGame->mWindow.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(evnt.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(evnt.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow->close();
			break;
		}

	}
}
//update position
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

//render sprites on the screen
void MainScene::render()
{
	mWindow->clear(sf::Color::Black);
	drawLines();
	mWindow->draw(mBlock);
	mWindow->display();
}

void MainScene::handlePlayerInput(sf::Keyboard::Key key,
	bool isPressed)
{

}

