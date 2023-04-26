#include "Demon.h"
#include <iostream>
#include "Pacman.h"
#include "Cookie.h"
#include "Wall.h"
#include "Door.h"

// a function thats sets the demon's position
void Demon::SetPosition(sf::Vector2f new_pos)
{
	m_sprite.setPosition(getCenter(new_pos));
}

// a function thats returns the demon's direction
Direction_t Demon::getDirection()
{
	return m_direction;
}

// a function thats signs a collision with a wall
void Demon::collide(Wall *object, Level &m_level)
{
	m_sprite.setPosition(getCenter(m_prevPos));
	wallCollision = true;
}

// a function thats signs a collision with a door
void Demon::collide(Door *object, Level &m_level)
{
	m_sprite.setPosition(getCenter(m_prevPos));
	doorCollision = true;
}

// a function thats  reutrns a random directio for the demon
Direction_t Demon::getRandDirection()
{
	Direction_t arr[] = {LEFT, RIGHT, UP, DOWN};
	
	return arr[rand() % 4];
}

// a function thats sets the demon's color
void Demon::SetColor(Color_t new_color)
{
	m_color = new_color;
	m_sourceX = m_color * 2;
}

// a function thats draws the demon
void Demon::draw(sf::RenderWindow &window, float passedTime)
{
	m_frameCounter += passedTime * REGULAR_SPEED;
	if (m_frameCounter > SWITCH_FRAME)
	{
		m_frameCounter = 0;
		m_sourceX++;
		if (m_sourceX > m_color * 2 + 1)
			m_sourceX = m_color * 2;
	}
	m_sprite.setTextureRect(sf::IntRect(m_sourceX * P_SIZE, m_direction * P_SIZE, P_SIZE, P_SIZE));
	window.draw(m_sprite);
}
