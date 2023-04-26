#pragma once
#include "Demon.h"

class SmartDemon : public Demon
{
public:
	SmartDemon() {};
	SmartDemon(Color_t color);

	void move(float passedTime,
		sf::Vector2f boardSize,
		const vector<std::vector<sf::Vector3i>> &Tree);

	Direction_t getBfsDirection(const sf::Vector2i & start,
		const sf::Vector2i &destination);
};


