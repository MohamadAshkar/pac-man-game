#include "RandomDemon.h"

#include <iostream>

// RandomDemon
RandomDemon::RandomDemon(Color_t color)
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(DEMON)));
	m_sprite.setOrigin(getCenter(m_sprite.getPosition()));
	SetPosition(m_sprite.getOrigin());
	m_direction = RIGHT;
	SetColor(color);
}

// a function thats moves the random demons
void RandomDemon::move(float passedTime, sf::Vector2f boardSize, const vector<std::vector<sf::Vector3i>> &Tree)
{
	m_prevPos = m_sprite.getPosition();
	float distance = REGULAR_SPEED * passedTime;
	int switchDirection = (rand() % 10);

	if ((passedTime > switchDirection || wallCollision) &&
		isCentered(m_sprite.getPosition(), getCenter(m_sprite.getPosition())))
	{
		wallCollision = false;
		m_moving = true;
		m_direction = getRandDirection();
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
