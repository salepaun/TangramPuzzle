#pragma once
#include <SFML/Graphics.hpp>

namespace sf
{
	class Block : public sf::Shape
	{
	public:
		Block(sf::Color &color, sf::Vector2f &position);

		virtual std::size_t getPointCount() const;
		virtual Vector2f getPoint(std::size_t index) const;
	private:
		virtual void draw(sf::RenderTarget& target, RenderStates states) const;
		
	private:
		sf::RectangleShape mShape;
		sf::Rect<float> mRect;
		sf::Vector2f position;
		
	};

}
