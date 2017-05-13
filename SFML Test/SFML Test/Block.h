#pragma once
#include <SFML/Graphics.hpp>

namespace sf
{
	class Block : public sf::Shape
	{
	public:
		Block(sf::Vector2f &position);

		virtual std::size_t getPointCount() const;
		virtual Vector2f getPoint(std::size_t index) const;
		bool contains(sf::Vector2f &pos, sf::Vector2f &relativeTo = sf::Vector2f());
		void setColor(sf::Color &color);
		virtual sf::Vector2f getPosition() const;
	private:
		virtual void draw(sf::RenderTarget& target, RenderStates states) const;
		
	private:
		sf::RectangleShape mShape;
		sf::Rect<float> mRect;
		sf::Vector2f position;
		
	};

}
