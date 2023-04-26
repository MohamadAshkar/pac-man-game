#include "SmartDemon.h"
#include <iostream>

// SmartDemon
SmartDemon::SmartDemon(Color_t color)
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(DEMON)));
	m_sprite.setOrigin(getCenter(m_sprite.getPosition()));
	SetPosition(m_sprite.getOrigin());
	m_direction = RIGHT;
	SetColor(color);
}

// a function thats moves the smart demons
void SmartDemon::move(float passedTime, sf::Vector2f boardSize, const vector<std::vector<sf::Vector3i>> &Tree)
{
	sf::Vector2i start = sf::Vector2i((int)(m_sprite.getPosition().x / P_SIZE),
									  (int)(m_sprite.getPosition().y / P_SIZE));

	m_prevPos = m_sprite.getPosition();
	float distance = REGULAR_SPEED * passedTime;

	if (isCentered(m_sprite.getPosition(), getCenter(m_sprite.getPosition())))
	{

		m_direction = getBfsDirection(start,
									  sf::Vector2i(Tree[start.y][start.x].y, Tree[start.y][start.x].z));
	}

	switch (m_direction)
	{
	case UP:
		m_sprite.move(0, -distance);
		break;
	case DOWN:
		m_sprite.move(0, distance);
		break;
	case RIGHT:
		m_sprite.move(distance, 0);
		break;
	case LEFT:
		m_sprite.move(-distance, 0);
		break;
	}

	if (outOfBoard(boardSize))
		m_sprite.setPosition(m_prevPos);
	m_pos = m_sprite.getPosition();
}

// a function thats returns a direction according to a bfs tree
Direction_t SmartDemon::getBfsDirection(const sf::Vector2i &start, const sf::Vector2i &destination)
{
	if (start.x > destination.x)
		return LEFT;

	if (start.x < destination.x)
		return RIGHT;

	if (start.y > destination.y)
		return UP;

	if (start.y < destination.y)
		return DOWN;
}
