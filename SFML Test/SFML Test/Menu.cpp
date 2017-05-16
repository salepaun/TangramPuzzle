#include "Menu.h"
#include "Game.h"
#include <iostream>
#include "System.h"

#define PLAY 0
#define EXIT 1

Menu::Menu(sf::RenderWindow* window, Game *game)
{
	mGame = game;
	mWindow = window;
	if (!mFont.loadFromFile("neuropol x rg.ttf"))
	{
		//handle error
		std::cout << "error mFont" << std::endl;
		mWindow->close();
		return;
	}
	
	centerText(menu[0], "Play", System::HEIGHT / (MAX_NUMBER_OF_ITEMS + 1),color(Red));
	centerText(nText, N_STRING, System::HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) + 100);
	centerText(menu[1], "Exit", System::HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) + 200);

	/*menu[1].setFont(mFont);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(WIDTH / 3, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(mFont);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(WIDTH / 3, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 3));*/

	selectedItemIndex = 0;

	up = down = enter = false;
	/*sf::Texture texture;
	if (!texture.loadFromFile("menu.png"))
	{
		std::cout << "background" << std::endl;
		mWindow->close();
		return;
	}
	mBackground = sf::Sprite(texture);
	mBackground.setPosition(0, 0);*/
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	up = false;
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	down = false;
}

int Menu::GetPressedItem() const
{
	return selectedItemIndex;
}

void Menu::run()
{
	while (mGame->mWindow.isOpen())
	{
		processEvents();
		update();
		render();
		if (!mGame->menu)return;
	}
}

void Menu::handlePlayerInput(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Up || key == sf::Keyboard::W)
		up = true;
	else if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
		down = true;
	else if (key == sf::Keyboard::Return)
		enter = true;
	else if (key == sf::Keyboard::Num5)
		setN(5);
	else if (key == sf::Keyboard::Num6)
		setN(6);
	//else if (key == sf::Keyboard::Num7)
	//	setN(7);
}

void Menu::processEvents()
{
	sf::Event evnt;
	while (mWindow->pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(evnt.key.code);
			break;
		case sf::Event::Closed:
			mGame->mWindow.close();
			break;
		}

	}
}

void Menu::update()
{
	if (up) MoveUp();
	else if (down) MoveDown();
	else if (enter)
	{
		switch (GetPressedItem())
		{
		case PLAY:
			mGame->menu = false;
			break;
		case EXIT:
			mWindow->close();
			break;
		}
	}
}

void Menu::render() const
{
	mWindow->clear(sf::Color(30, 144, 255));
	//mWindow->draw(mBackground);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		mWindow->draw(menu[i]);
	}
	mWindow->draw(nText);
	mWindow->display();
}

void Menu::centerText(sf::Text & text, std::string value, float height, sf::Color & clr)
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

void Menu::setN(int num)
{
	sf::String str = nText.getString();
	str[3] = num + '0';
	nText.setString(str);
	System::N = num;
	switch (num)
	{
	case 5: System::M = 7;
		break;
	case 6: System::M = 8;
		break;
	case 7: System::M = 9;
		break;
	}
}
