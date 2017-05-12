#pragma once
#include <SFML/Graphics/Shape.hpp>
#include "Block.h"

namespace sf
{
	class WeirdShape : public sf::Shape
	{
	public:
		WeirdShape();

		void draw(sf::RenderTarget& target, RenderStates states) const;

		virtual std::size_t getPointCount() const;
		virtual Vector2f getPoint(std::size_t index) const;
		void addBlock(sf::Block &block);
		Vector2f hold(sf::Vector2f &pos);
		void setBlockColor(sf::Color &color);
	private:
		std::vector<sf::Block> mBlocks;
	};

}
