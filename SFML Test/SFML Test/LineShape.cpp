#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "LineShape.h"


namespace sf
{

	LineShape::LineShape(const Vector2f& point1, const Vector2f& point2) :
		m_direction(point2 - point1)
	{
		setPosition(point1);
		setThickness(THICKNESS);
		//setFillColor(sf::Color(sf::Color::Black));
	}

	LineShape::LineShape() :
		m_direction()
	{
		setThickness(THICKNESS);
	}

	void LineShape::setDirection(sf::Vector2f & dir)
	{
		m_direction = dir;
	}

	void LineShape::setThickness(float thickness)
	{
		m_thickness = thickness;
		update();
	}

	float LineShape::getThickness() const
	{
		return m_thickness;
	}

	float LineShape::getLength() const
	{
		return std::sqrt(m_direction.x*m_direction.x + m_direction.y*m_direction.y);
	}

	unsigned int LineShape::getPointCount() const
	{
		return 4;
	}

	Vector2f LineShape::getPoint(unsigned int index) const
	{
		Vector2f unitDirection = m_direction / getLength();
		Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

		Vector2f offset = (m_thickness / 2.f)*unitPerpendicular;

		switch (index)
		{
		default:
		case 0: return offset;
		case 1: return (m_direction + offset);
		case 2: return (m_direction - offset);
		case 3: return (-offset);
		}
	}

} // namespace sf