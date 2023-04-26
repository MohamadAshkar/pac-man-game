#include "Pacman.h"

// Pacman

Pacman::Pacman()
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(PACMAN)));
	m_sprite.setOrigin(getCenter(m_sprite.getPosition()));
	SetPosition(m_sprite.getOrigin());
	m_sounds[MUNCH].setBuffer(*(FileManager::instance().getPacmanSound(MUNCH)));
	m_sounds[DEATH].setBuffer(*(FileManager::instance().getPacmanSound(DEATH)));
	m_sounds[POISON_COOKIE].setBuffer(*(FileManager::instance().getPacmanSound(POISON_COOKIE)));
	m_sounds[HEALTH_COOKIE].setBuffer(*(FileManager::instance().getPacmanSound(HEALTH_COOKIE)));
	m_superPacman = false;
	m_healthCookieTimer = 0;
	m_poisonCookieTimer = 0;
	m_superPacmanTimer = 0;
	m_stopDemonTimer = 0;
}

// a function thats sets the pacmans position

void Pacman::SetPosition(sf::Vector2f new_pos)
{
	m_sprite.setPosition(getCenter(new_pos));
}

// a function thats sets the pacman's color
void Pacman::SetColor(Color_t new_color)
{
	m_color = new_color;
	m_sourceX = m_color * 2;
}

// a function thats sets the pacman's direction
void Pacman::setDirection(sf::Keyboard::Key direction)
{
	switch (direction)
	{
	case sf::Keyboard::Left:
		m_newDirection = LEFT;
		break;
	case sf::Keyboard::Right:
		m_newDirection = RIGHT;
		break;
	case sf::Keyboard::Up:
		m_newDirection = UP;
		break;
	case sf::Keyboard::Down:
		m_newDirection = DOWN;
		break;
	}
}

// a function thats draws the pacman
void Pacman::draw(sf::RenderWindow &window, float passedTime)
{
	if (m_cookieCounter == 0 || m_isEaten)
	{
		m_direction = RIGHT;
		m_speed = REGULAR_SPEED;
	}
	m_frameCounter += passedTime * m_speed;

	if (m_frameCounter > SWITCH_FRAME)
	{
		m_frameCounter = 0;
		m_sourceX++;
		if (m_sourceX > m_color * 2 + 1)
			m_sourceX = m_color * 2;
	}

	m_sprite.setTextureRect(sf::IntRect(m_sourceX * P_SIZE, m_direction * P_SIZE, P_SIZE, P_SIZE));
	window.draw(m_sprite);
}

// a function thats checks the timers of the special cookies
void Pacman::checkSpeacialCookie(float passedTime)
{
	if (m_healthCookieTimer > 0)
		m_healthCookieTimer = m_healthCookieTimer - passedTime;
	else if (m_poisonCookieTimer > 0)
		m_poisonCookieTimer = m_poisonCookieTimer - passedTime;
	else
		m_speed = REGULAR_SPEED;

	if (m_superPacmanTimer > 0)
		m_superPacmanTimer = m_superPacmanTimer - passedTime;
	if (m_stopDemonTimer > 0)
		m_stopDemonTimer = m_stopDemonTimer - passedTime;
}

// a function thats moves the pacman
void Pacman::move(float passedTime, sf::Vector2f boardSize)
{
	m_prevPos = m_sprite.getPosition();
	checkSpeacialCookie(passedTime);
	float distance = m_speed * passedTime;

	if (isCentered(m_sprite.getPosition(), getCenter(m_sprite.getPosition())))
		m_direction = m_newDirection;

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
		m_sprite.setPosition(getCenter(m_prevPos));
	m_pos = m_sprite.getPosition();
}

// a function thats returns the pacman's direction
Direction_t Pacman::getDirection()
{
	return m_direction;
}

// a function thats returns the pacman's lives number
int Pacman::getLife()
{
	return m_life;
}

// a function thats return if the pacman was eaten by a demon
bool Pacman::getPacmanState()
{
	return m_isEaten;
}

// a function thats sets the pacman's state
void Pacman::setPacmanState()
{
	m_isEaten = false;
}

// a function thats sets the cookie counter
void Pacman::setCookieCounter(int x)
{
	m_cookieCounter += x;
}

// a function thats return the cookie counter
int Pacman::getCookies() const
{
	return m_cookieCounter;
}

// a function thats return the player's score
int Pacman::getScore() const
{
	return m_score;
}

// a function thats sets the player's lives
void Pacman::setLife(int x)
{
	if (m_life < 3)
		m_life += x;
}

// a function thats sets the player's score
void Pacman::setScore(int x)
{
	m_score += x;
}

//  this function get cuonter of super-pacman
float Pacman::getSuperPacmanTimer()
{
	return m_superPacmanTimer;
}

float Pacman::stopDemonTimer()
{
	return m_stopDemonTimer;
}

//  this function get if super-pacman
bool Pacman::getSuper() const
{
	return m_superPacman;
}

//  this function set super-pacman
void Pacman::setSuper(bool super)
{
	m_superPacman = super;
}

void Pacman::addTime(int add)
{
	m_addTime = add;
}

int Pacman::getAddTime()
{
	return m_addTime;
}

void Pacman::setStop(bool stop)
{
	m_stopDemon = stop;
}

bool Pacman::getStopDemon()
{
	return m_stopDemon;
}

// a function thats signs a collision with a demon
void Pacman::collide(Demon *object, Level &m_level)
{
	if (!(this->getSuper()))
	{
		m_life--;
		m_isEaten = true;
		m_sounds[DEATH].play();
	}
}

// a function thats signs a collision with a cookie
void Pacman::collide(Cookie *object, Level &m_level)
{

	sf::Vector2f objPos;
	objPos.x = object->getPosition().x * P_SIZE + P_SIZE / 2;
	objPos.y = object->getPosition().y * P_SIZE + P_SIZE / 2;
	if (abs(m_sprite.getPosition().x - objPos.x) < P_SIZE / 2 &&
		abs(m_sprite.getPosition().y - objPos.y) < P_SIZE / 2 &&
		object->getState())
	{
		setScore(SCORE_COOKIE);
		object->setState(false);
		setCookieCounter(-1);
		m_sounds[MUNCH].play();

		if (object->getCookieColor() == sf::Color::Green)
		{
			if (m_speed <= 150)
				m_speed *= 1.2;
			m_healthCookieTimer = HEALTH_COOKIE_TIME;
			m_poisonCookieTimer = 0;
		}
		else if (object->getCookieColor() == sf::Color::Red)
		{
			m_speed *= 0.9;
			m_poisonCookieTimer = POISON_COOKIE_TIME;
			m_healthCookieTimer = 0;
		}
	}
}

// a function thats signs a collision with a wall
void Pacman::collide(Wall *object, Level &m_level)
{
	m_sprite.setPosition(getCenter(m_prevPos));
}

// a function thats signs a collision with a door
void Pacman::collide(Door *object, Level &m_level)
{
	if (this->getSuper() && object->getState())
	{
		setScore(SCORE_KEY);
		m_sounds[MUNCH].play();
		object->setState(false);
		m_level.clearBoard(m_level.getNumberOfLevel(), '%');
	}
	if (object->getState())
		m_sprite.setPosition(getCenter(m_prevPos));
}

void Pacman::collide(Key *object, Level &m_level)
{
	sf::Vector2f objPos;
	objPos.x = object->getPosition().x * P_SIZE + P_SIZE / 2;
	objPos.y = object->getPosition().y * P_SIZE + P_SIZE / 2;

	if ((abs(m_sprite.getPosition().x - objPos.x) < P_SIZE / 2 &&
		 abs(m_sprite.getPosition().y - objPos.y) < P_SIZE / 2 &&
		 object->getState()))
	{
		m_level.clearBoard(m_level.getNumberOfLevel(), 'D');

		setScore(SCORE_KEY);
		object->setState(false);
		m_sounds[MUNCH].play();
	}
}

void Pacman::collide(Gift *object, Level &m_level)
{
	sf::Vector2f objPos;
	objPos.x = object->getPosition().x * P_SIZE + P_SIZE / 2;
	objPos.y = object->getPosition().y * P_SIZE + P_SIZE / 2;
	if (abs(m_sprite.getPosition().x - objPos.x) < P_SIZE / 2 &&
		abs(m_sprite.getPosition().y - objPos.y) < P_SIZE / 2 &&
		object->getState())
	{
		setScore(SCORE_GIFT);
		object->setState(false);
		m_sounds[HEALTH_COOKIE].play();

		int switchGift = (rand() % 3);
		switch (switchGift)
		{
		case ADD_LIFE:
			setLife(1);
		case STOP_DEMON:
			m_stopDemonTimer = STOP_DEMON_TIME;
			setStop(true);
		case INC_TIME:
			addTime(10);
		default:
			break;
		}
	}
}

void Pacman::collide(Superpacman *object, Level &m_level)
{
	sf::Vector2f objPos;
	objPos.x = object->getPosition().x * P_SIZE + P_SIZE / 2;
	objPos.y = object->getPosition().y * P_SIZE + P_SIZE / 2;
	if (abs(m_sprite.getPosition().x - objPos.x) < P_SIZE / 2 &&
		abs(m_sprite.getPosition().y - objPos.y) < P_SIZE / 2 &&
		object->getState())
	{
		setScore(SCORE_GIFT);
		object->setState(false);
		m_sounds[POISON_COOKIE].play();
		m_level.setPacman(*this, RED, this->getPosition());
		this->setKey(true);
		m_superPacman = true;
		m_superPacmanTimer = SUPER_PACMAN_TIME;
		m_healthCookieTimer = 0;
		m_poisonCookieTimer = 0;
	}
}
