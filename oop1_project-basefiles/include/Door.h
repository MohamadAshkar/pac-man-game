#pragma once
#include "StaticIcon.h"
#include "Pacman.h"
#include "Demon.h"
#include "Wall.h"
#include "Cookie.h"
#include "Key.h"
#include "Gift.h"
#include "Superpacman.h"

class Pacman;
class Wall;
class Demon;
class Cookie;
class Key;
class Gift;
class Superpacman;
class Level;


class Door : public StaticIcon
{
public:
	Door();
	
	Door(sf::Color color);
	void draw(sf::RenderWindow& window, sf::Vector2f pos)
	{
		if (getState()) {
			//m_sprite.setColor(m_color);
			m_sprite.setPosition(pos);
			window.draw(m_sprite);
		}
	}
	~Door();
	virtual void collide(Icon* object, Level& m_level);
	virtual void collide(Key* object, Level& m_level) {};
	virtual void collide(Pacman* object, Level& m_level);
	virtual void collide(Demon* object, Level& m_level);
	virtual void collide(Cookie* object, Level& m_level) {};
	virtual void collide(Wall* object, Level& m_level) {};
	virtual void collide(Door* object, Level& m_level) {};
	virtual void collide(Gift* object, Level& m_level){};
	virtual void collide(Superpacman* object, Level& m_level) {};
	
	virtual bool getState()const { return m_state; }
	virtual void setState(bool s) { m_state = s; }
	
private:
	

};


