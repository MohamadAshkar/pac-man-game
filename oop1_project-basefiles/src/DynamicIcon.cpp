#include "DynamicIcon.h"

// a function thats  returns a the dircetio for either a pacman
// or a demon

Direction_t DynamicIcon::getDirection()
{
	return m_direction;
}

// a function thats returns the direction according the the objects next
// position
sf::Vector2f DynamicIcon::getNextDirection(Direction_t direction)
{
	sf::Vector2f nextPos = m_sprite.getPosition();

	switch (direction)
	{
	case UP:
		return sf::Vector2f(nextPos.x, nextPos.y - (P_SIZE / 2));
	case DOWN:
		return sf::Vector2f(nextPos.x, nextPos.y + (P_SIZE / 2));
	case RIGHT:
		return sf::Vector2f(nextPos.x + (P_SIZE / 2), nextPos.y);
	case LEFT:
		return sf::Vector2f(nextPos.x - (P_SIZE / 2), nextPos.y);
	}
}

// a function thats returns the objects statring position
sf::Vector2f DynamicIcon::getStartingPosition()
{
	return m_startingPosition;
}

// a function thats  returns the objects current position
sf::Vector2f DynamicIcon::getPosition()
{
	return m_sprite.getPosition();
}

// a function thats sets the object's position to it's starting
// position
void DynamicIcon::setStartingPosition(sf::Vector2f pos)
{
	m_startingPosition = pos;
}

// a function thats checks if the object's position in at the center of
// a cell in the board
bool DynamicIcon::isCentered(sf::Vector2f pos, sf::Vector2f center)
{
	return abs(pos.x - center.x) < DIFF_SIZE && abs(pos.y - center.y) < DIFF_SIZE;
}

// a function thats returns if an object is out of the board
bool DynamicIcon::outOfBoard(sf::Vector2f size)
{
	int distance = P_SIZE / 2;
	return m_sprite.getPosition().x + distance > size.y || m_sprite.getPosition().y + distance > size.x ||
		   m_sprite.getPosition().x - distance < 0 || m_sprite.getPosition().y - distance < 0;
}

// a function thats returns the center of a certain cell in the board
// it gets a certain position in the board
sf::Vector2f DynamicIcon::getCenter(sf::Vector2f pos)
{
	sf::Vector2f newPos;
	newPos.x = (pos.x - ((int)pos.x % P_SIZE)) + P_SIZE / 2;
	newPos.y = (pos.y - ((int)pos.y % P_SIZE)) + P_SIZE / 2;
	return newPos;
}
