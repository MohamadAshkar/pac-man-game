#include "Wall.h"
#include "Pacman.h"
#include "Demon.h"
#include "Cookie.h"

// this class inherates from the Static icon class

Wall::Wall()
{
}

// a function thats used for drawing the wall on the window
// according the position
void Wall::draw(sf::RenderWindow &window, sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
	window.draw(m_sprite);
}

// defines the color of the wall
Wall::Wall(sf::Color color)
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(WALL)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
								   ((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	m_sprite.setColor(color);
}

Wall::~Wall()
{
}

//  defines the collision of the Wall with the icons
void Wall::collide(Icon *object, Level &m_level)
{
	object->collide(this, m_level);
}

//  defines the collision of the Wall with the Pacman
void Wall::collide(Pacman *object, Level &m_level)
{
	object->collide(this, m_level);
}
//  defines the collision of the Wall with the Demon
void Wall::collide(Demon *object, Level &m_level)
{
	object->collide(this, m_level);
}
