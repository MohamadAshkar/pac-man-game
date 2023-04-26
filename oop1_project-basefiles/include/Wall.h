#pragma once
#include "StaticIcon.h"
#include "Pacman.h"
#include "Demon.h"
#include "Cookie.h"
#include "Door.h"
#include "Key.h"
#include "Gift.h"
#include "Superpacman.h"


class Pacman;
class Cookie;
class Demon;
class Door;
class Level;
class Key;
class Gift;
class Superpacman;

class Wall : public StaticIcon
{
public:
	Wall();
	void draw(sf::RenderWindow &window, sf::Vector2f pos);
	Wall(sf::Color color);
	~Wall();
	virtual void collide(Icon * object, Level & m_level);
	virtual void collide(Pacman * object, Level & m_level);
	virtual void collide(Demon * object, Level & m_level);
	virtual void collide(Cookie * object, Level & m_level) {};
	virtual void collide(Wall * object, Level & m_level) {};
	virtual void collide(Door* object, Level& m_level) {};
	virtual void collide(Key* object, Level& m_level){};
	virtual void collide(Gift* object, Level& m_level){};
	virtual void collide(Superpacman* object, Level& m_level) {};

private:

};


