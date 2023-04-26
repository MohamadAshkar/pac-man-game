#include "Door.h"

Door::Door()
{
	m_state = true;
}

Door::Door(sf::Color color)
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(DOOR)));

	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),

								   ((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	m_sprite.setColor(color);
}

Door::~Door()
{
}
//  defines the collision of the Door with the icons
void Door::collide(Icon *object, Level &m_level)
{
	object->collide(this, m_level);
}

//  defines the collision of the Door with the Pacman
void Door::collide(Pacman *object, Level &m_level)
{
	object->collide(this, m_level);
}

//  defines the collision of the Door with the Demon
void Door::collide(Demon *object, Level &m_level)
{
	object->collide(this, m_level);
}
