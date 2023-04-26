#pragma once
#include "DynamicIcon.h"
#include <iostream>
#include "Demon.h"
#include "Cookie.h"
#include "Wall.h"
#include "Door.h"
#include "Key.h"
#include "Gift.h"
#include "Level.h"
#include "Superpacman.h"


enum {ADD_LIFE, STOP_DEMON, INC_TIME};

const int SUPER_PACMAN_TIME = 7;
const int HEALTH_COOKIE_TIME = 14;
const int POISON_COOKIE_TIME = 7;
const int STOP_DEMON_TIME = 7;



class Pacman : public DynamicIcon
{
public:
	Pacman();

	void SetPosition(sf::Vector2f new_pos);
	void SetColor(Color_t new_color);
	void setDirection(sf::Keyboard::Key direction);
	
	void draw(sf::RenderWindow &window, float passedTime);
	void move(float passedTime, sf::Vector2f boardSize);
	Direction_t getDirection();
	int getLife();
	bool getPacmanState();
	void setPacmanState();
	void setCookieCounter(int x);
	int getCookies() const;
	int getScore() const;
	void setLife(int x);
	void setScore(int x);
	float getSuperPacmanTimer();
	float stopDemonTimer();
	bool getSuper()const;
	void setSuper(bool super);
	void addTime(int add);
	int getAddTime();
	void setStop(bool add);
	bool getStopDemon();

	virtual void collide(Icon * object, Level & m_level) {};
	virtual void collide(Pacman * object, Level & m_level) {};
	virtual void collide(Demon * object, Level & m_level) ;
	virtual void collide(Cookie * object, Level & m_level) ;
	virtual void collide(Wall * object, Level & m_level);
	virtual void collide(Door* object, Level& m_level);
	virtual void collide(Key* object, Level& m_level);
	virtual void collide(Gift* object, Level& m_level);
	virtual void collide(Superpacman* object, Level& m_level);
	


private:
	void checkSpeacialCookie(float passedTime);
	float m_healthCookieTimer;
	float m_poisonCookieTimer;
	float m_superPacmanTimer;
	float m_stopDemonTimer;
	int m_cookieCounter;
	Color_t m_color;
	float m_speed = 5;
	int m_sourceX = 0;
	Direction_t m_newDirection;
	int m_score = 0;
	int m_life = 3;
	bool m_isEaten;
	int m_numOfDemons;
	sf::Sound m_sounds[NUM_OF_SOUNDS-2];
	bool m_superPacman;
	int m_addTime = 0;
	bool m_stopDemon;
};

