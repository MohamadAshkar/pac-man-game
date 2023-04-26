#pragma once
#include "DynamicIcon.h"
#include <time.h>



class Demon : public DynamicIcon
{
public:
	Demon() {};


	void draw(sf::RenderWindow &window, float passedTime);
	virtual void move(float passedTime, sf::Vector2f boardSize, const vector<std::vector<sf::Vector3i>> &Tree) {};
	void SetPosition(sf::Vector2f new_pos);
	Direction_t getDirection();

	virtual void collide(Icon * object, Level & m_level) {};
	virtual void collide(Pacman * object, Level & m_level) {};
	virtual void collide(Demon * object, Level & m_level) {};
	virtual void collide(Cookie * object, Level & m_level) {};
	virtual void collide(Wall * object, Level & m_level) ;
	virtual void collide(Door * object, Level& m_level);
	virtual void collide(Key* object, Level& m_level) {};
	virtual void collide(Gift* object, Level& m_level) {};
	virtual void collide(Superpacman* object, Level& m_level) {};



protected:
	Direction_t getRandDirection();
	bool m_moving;
	void SetColor(Color_t new_color);
	int m_sourceX = 0;
	Color_t m_color;
	bool wallCollision = false;
	bool doorCollision = false;
	Direction_t m_newDirection;

};


