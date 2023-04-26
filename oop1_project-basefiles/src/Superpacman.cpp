#include "Superpacman.h"

Superpacman::Superpacman()
{
	m_state = true;
}

Superpacman::Superpacman(sf::Color color, sf::Vector2i Pos)
{
	m_pos = Pos;
	m_color = color;
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(SUPERPACMAN)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
								   ((float)P_SIZE / m_sprite.getGlobalBounds().height)));
}

Superpacman::~Superpacman()
{
}

void Superpacman::collide(Icon *object, Level &m_level)
{
	object->collide(this, m_level);
}

void Superpacman::collide(Pacman *object, Level &m_level)
{
	object->collide(this, m_level);
}

sf::Vector2i Superpacman::getPosition()
{
	return m_pos;
}

sf::Color Superpacman::getSuperColor()
{
	return m_color;
}

bool Superpacman::getState() const
{
	return m_state;
}

void Superpacman::setState(bool s)
{
	m_state = s;
}
