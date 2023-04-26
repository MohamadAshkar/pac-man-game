#pragma once
#include <SFML\Graphics.hpp>
#include "FileManager.h"

class PlayerStates
{
public:
	PlayerStates();
	~PlayerStates() {};
	void draw(sf::RenderWindow & window, int life, int score, int level, int timer, sf::Vector2f Boardhight);
private:
	sf::Text m_statusBar;
	sf::Font m_font;
	sf::Sprite m_lifeSpirte;
};

