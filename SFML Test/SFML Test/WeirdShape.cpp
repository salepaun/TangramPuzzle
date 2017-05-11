#include "WeirdShape.h"



sf::WeirdShape::WeirdShape():
	mBlocks()
{
	
}


void sf::WeirdShape::draw(sf::RenderTarget & target, RenderStates states) const
{
	for (auto &block : mBlocks)
		target.draw(block, states);
}
