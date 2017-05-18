#pragma once
#include <SFML/Graphics/Shape.hpp>
#include "Block.h"

namespace sf
{
	class WeirdShape : public sf::Shape
	{
	public:
		WeirdShape();

		void draw(sf::RenderTarget& target, RenderStates states) const override;

		std::size_t getPointCount() const override;
		Vector2f getPoint(std::size_t index) const override;
		void addBlock(sf::Block &block);
		Vector2f hold(sf::Vector2f &pos);
		void setBlockColor(sf::Color &color);
		Vector2f getBlockPoint(Vector2f &mousePosition);
		std::vector<sf::Block>& getBlocks();
		char getMark() const;
		bool isInGrid() const;
		void setInGrid(bool status);

		static char next;
	private:
		std::vector<sf::Block> mBlocks;
		char mark;
		bool inGrid;
	};

}
