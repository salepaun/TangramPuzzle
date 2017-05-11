#include "Block.h"
#include "Game.h"

sf::Block::Block(sf::Color &color, sf::Vector2f& position)
{
	
	mShape.setFillColor(color);
	mShape.setPosition(position);
	mShape.setSize(Vector2f(WIDTH / (N + 2), WIDTH / (N + 2)));

	mRect = sf::Rect<float>(position, Vector2f(mShape.getSize()));
}

std::size_t sf::Block::getPointCount() const
{
	return mShape.getPointCount();
}

sf::Vector2f sf::Block::getPoint(std::size_t index) const
{
	return mShape.getPoint(index);
}

void sf::Block::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mShape, states);
}
