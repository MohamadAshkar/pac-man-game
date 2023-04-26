#include "Cookie.h"

// this class extends from Static icon class
Cookie::Cookie()
{
	m_state = true;
}

//  each cookie gets color, position, size
Cookie::Cookie(sf::Color color, sf::Vector2i pos)
{
	m_pos = pos;
	m_color = color;
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(COOKIE)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
								   ((float)P_SIZE / m_sprite.getGlobalBounds().height)));
}

Cookie::~Cookie()
{
}

//  defines the collision of the cookie with icons
void Cookie::collide(Icon *object, Level &m_level)
{
	object->collide(this, m_level);
}

//  defines the collision of the cookie with the pacman
void Cookie::collide(Pacman *object, Level &m_level)
{
	object->collide(this, m_level);
}

// return the position of the cookie

sf::Vector2i Cookie::getPosition()
{
	return m_pos;
}

// return the color of the cookie
sf::Color Cookie::getCookieColor()
{
	return m_color;
}

bool Cookie::getState() const
{
	return m_state;
}

void Cookie::setState(bool s)
{
	m_state = s;
}
