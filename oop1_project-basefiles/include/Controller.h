#pragma once

#include "Level.h"
#include <iostream>
#include <string>
#include <queue>
#include "PlayerStates.h"


const int NUM_OF_LEVELS = 6;

class Controller
{
public:
	Controller();
	~Controller();
	void setDirection(sf::Event newEvent,bool & isMoving, sf::Clock & clock);
	bool run(sf::RenderWindow & window, int highScores[], sf::Music & backroundMusic,int & i);
	void checkCollision(DynamicIcon * character, Direction_t direction);
	void setPacmanDirection(sf::Keyboard::Key direction);
	void moveDynamic(sf::RenderWindow & window, float passedTime, bool & isMoving);
	void set_Level_value(const int value);
	//int getNumberLevel();



private:
	void resetGame(sf::RenderWindow & window, bool & isMoving);
	void checkEvent(sf::RenderWindow & window, sf::Clock & clock, sf::Event Event, bool & isMoving, sf::Music & backroundMusic);
	bool checkForHs(int highScores[], int score,int & i);
	void mute(sf::Music & backroundMusic);
	
	bool m_mute = false;
	
	void drawGetReady(sf::RenderWindow & window);
	sf::Sound m_sound[NUM_OF_SOUNDS - 4];
	void draw(sf::RenderWindow & window, float passedTime, int curr_time);
	bool levelFinished();
	PlayerStates m_statesBar;
	vector<std::vector<sf::Vector3i>> getBfsTree(sf::Vector2i start, const vector <vector<std::unique_ptr<StaticIcon>>> & board);
	vector<sf::Vector2i> getNeighbors(const sf::Vector2i center, const vector <vector<std::unique_ptr<StaticIcon>>> & board);
	bool OutOfBoard(sf::Vector2f place, const vector <vector<std::unique_ptr<StaticIcon>>> & board);
	int m_levelNumber = 1;
	void levelUp(bool & isMoving,sf::RenderWindow & window);
	bool atePacman(Demon *demon);
	void setDynamics(sf::RenderWindow & window, bool & isMoving);
	bool isOver();
	//int m_score;
	void drawDynamic(sf::RenderWindow & window, float passedTime);
	Pacman m_pacman;
	vector <std::unique_ptr<Demon>> m_demons;
	sf::Sprite m_sprites[NUM_OF_ICONS];
	Level m_level;
	sf::Font m_font;
	sf::Text m_getReady;
	int m_curr_time;

	
};

