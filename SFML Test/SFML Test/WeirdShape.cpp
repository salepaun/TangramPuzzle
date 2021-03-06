#include "WeirdShape.h"

char sf::WeirdShape::next = '0';

sf::WeirdShape::WeirdShape():
	 mBlocks()
	,inGrid(false)
{
	mark = next++;
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
		block.setColor(color);
	}
}

sf::Vector2f sf::WeirdShape::getBlockPoint(Vector2f & mousePosition)
{
	if(mBlocks.size()>0)
	for (auto &block : mBlocks)
	{
		if(block.contains(mousePosition,(sf::Vector2f)this->getPosition()))
		{
			return this->getPosition() + block.getPosition();
		}
	}
}

std::vector<sf::Block>& sf::WeirdShape::getBlocks()
{
	return mBlocks;
}

char sf::WeirdShape::getMark() const
{
	return mark;
}

bool sf::WeirdShape::isInGrid() const
{
	return inGrid;
}

void sf::WeirdShape::setInGrid(bool status)
{
	inGrid = status;
}
