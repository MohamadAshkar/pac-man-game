#pragma once
#include "Icon.h"

enum Direction_t {RIGHT, DOWN, LEFT, UP};

const int DIFF_SIZE = 5;
const float SWITCH_FRAME = 15;
const float REGULAR_SPEED = 120;

class DynamicIcon : public Icon
{
public:
	DynamicIcon() {};
	~DynamicIcon() {};

	
	virtual void draw(sf::RenderWindow &window) {}
	virtual void move(sf::Clock &clock, sf::Vector2f boardSize, bool & isMoving) {}
	Direction_t getDirection();
	sf::Vector2f getNextDirection(Direction_t direction);
	sf::Vector2f getStartingPosition();
	sf::Vector2f getPosition();
	void setStartingPosition(sf::Vector2f pos);
	bool getKey() { return m_haveKey; }
	void setKey(bool have) { m_haveKey = have; }

protected:
	sf::Vector2f m_startingPosition;
	bool isCentered(sf::Vector2f pos, sf::Vector2f center);
	bool outOfBoard(sf::Vector2f size);
	sf::Vector2f m_prevPos;
	sf::Vector2f getCenter(sf::Vector2f pos);
	sf::Vector2f m_pos;
	Direction_t m_direction;
	float m_frameCounter = 0;
	float m_distance = 0;
	bool m_haveKey = false;
	
};


