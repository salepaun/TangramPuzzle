#include "Block.h"
#include "Game.h"

sf::Block::Block(sf::Vector2f& position)
{
	
	mShape.setPosition(position);
	mShape.setSize(Vector2f(EDGE,EDGE));

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

bool sf::Block::contains(sf::Vector2f & pos)
{
	return	mRect.contains(pos.x, pos.y);
}

void sf::Block::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mShape, states);
}
