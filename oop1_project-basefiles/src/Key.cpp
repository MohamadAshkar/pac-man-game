#include "Key.h"

Key::Key()
{
	m_state = true;
}

Key::Key(sf::Color color, sf::Vector2i Pos)
{
	m_pos = Pos;
	m_color = color;
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(KEY)));

	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),

								   ((float)P_SIZE / m_sprite.getGlobalBounds().height)));
}

void Key::collide(Icon *object, Level &m_level)
{
	object->collide(this, m_level);
}

void Key::collide(Pacman *object, Level &m_level)
{
	object->collide(this, m_level);
}

sf::Vector2i Key::getPosition()
{
	return m_pos;
}

sf::Color Key::getCookieColor()
{
	return m_color;
}
