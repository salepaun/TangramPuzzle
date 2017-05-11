#pragma once
#include <SFML/Graphics/Shape.hpp>
#include "Block.h"

namespace sf
{
	class WeirdShape
	{
	public:
		WeirdShape();

		void draw(sf::RenderTarget& target, RenderStates states) const;
	private:
		std::vector<sf::Block> mBlocks;
	};

}
