#pragma once
#include "Demon.h"

class RandomDemon : public Demon
{
public:
	RandomDemon() {};
	~RandomDemon() {};
	RandomDemon(Color_t color);
	void move(float passedTime, sf::Vector2f boardSize,
		const vector<std::vector<sf::Vector3i>> &Tree);
};


