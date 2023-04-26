#pragma once

#include "StaticIcon.h"
#include "Pacman.h"
#include "Demon.h"
#include "Wall.h"
#include "Door.h"
#include "Key.h"
#include "Gift.h"

class Pacman;
class Wall;
class Demon;
class Door;
class Key;
class Cookie;
class Level;


class Superpacman : public StaticIcon
{
public:
	Superpacman ();
	Superpacman(sf::Color color, sf::Vector2i Pos);
	void draw(sf::RenderWindow& window, sf::Vector2f pos)
	{
		if (getState()) {
			m_sprite.setColor(m_color);
			m_sprite.setPosition(pos);
			window.draw(m_sprite);
		}
	}
	~Superpacman ();

	virtual void collide(Icon* object, Level& m_level);
	virtual void collide(Pacman* object, Level& m_level);
	virtual void collide(Demon* object, Level& m_level) {};
	virtual void collide(Cookie* object, Level& m_level) {};
	virtual void collide(Wall* object, Level& m_level) {};
	virtual void collide(Door* object, Level& m_level) {};
	virtual void collide(Key* object, Level& m_level) {};
	virtual void collide(Gift* object, Level& m_level) {};
	virtual void collide(Superpacman* object, Level& m_level) {};

	sf::Vector2i getPosition();
	sf::Color getSuperColor();

	virtual bool getState()const;
	virtual void setState(bool s);

private:
	sf::Color m_color;
	sf::Vector2i m_pos;
};
