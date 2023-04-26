#include "Gift.h"

Gift::Gift()
{
	m_state = true;
}

Gift::Gift(sf::Color color, sf::Vector2i Pos)
{
	m_pos = Pos;
	m_color = color;
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(GIFT)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
								   ((float)P_SIZE / m_sprite.getGlobalBounds().height)));
}

Gift::~Gift()
{
}

void Gift::collide(Icon *object, Level &m_level)
{
	object->collide(this, m_level);
}

void Gift::collide(Pacman *object, Level &m_level)
{
	object->collide(this, m_level);
}

sf::Vector2i Gift::getPosition()
{
	return m_pos;
}

sf::Color Gift::getCookieColor()
{
	return m_color;
}

bool Gift::getState() const
{
	return m_state;
}

void Gift::setState(bool s)
{
	m_state = s;
}
