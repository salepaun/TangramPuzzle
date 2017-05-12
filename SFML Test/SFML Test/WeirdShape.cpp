#include "WeirdShape.h"



sf::WeirdShape::WeirdShape():
	mBlocks()
{
	
}


void sf::WeirdShape::draw(sf::RenderTarget & target, RenderStates states) const
{
	states.transform *= this->getTransform();
	for (auto &block : mBlocks)
	{
		target.draw(block, states);
	}
}

std::size_t sf::WeirdShape::getPointCount() const
{
	size_t count = 0;
	for (auto &block : mBlocks)
		count += block.getPointCount();
	return  count;
}

sf::Vector2f sf::WeirdShape::getPoint(std::size_t index) const
{
	return mBlocks[index / 4].getPoint(index % 4);
}

void sf::WeirdShape::addBlock(sf::Block &block)
{
	mBlocks.push_back(block);
}

sf::Vector2f sf::WeirdShape::hold(sf::Vector2f &pos)
{
	/*for (auto &block : mBlocks)
	{
		if (block.contains(pos))
			return block.getPosition();
	}*/
	return pos - this->getPosition();
}

void sf::WeirdShape::setBlockColor(sf::Color & color)
{
	for (auto &block : mBlocks)
	{
		block.setFillColor(color);
	}
}
