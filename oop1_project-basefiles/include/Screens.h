#pragma once

#include "SFML\Graphics.hpp"
#include "FileManager.h"
#include "Controller.h"

const int TOP_5 = 5;

class Screens
{
public:
	Screens();
	~Screens();
	void runMenu();
	//void setScreens(sf::Sprite screens(int indix));

private:
	sf::Music m_backroundMusic;
	Menu_t getMenuButton(sf::Vector2i buttonPos);
	MAP_s getMapButton(sf::Vector2i buttonPos);
	ENTER_HS_h getEhsButton(sf::Vector2i buttonPos); //TODO
	HS_v getHsButton(sf::Vector2i buttonPos);
	GAME_OVER_f getGoButton(sf::Vector2i buttonPos); //TODO
	INTRO_a getIntrButton(sf::Vector2i buttonPos); 
	void getUpdatedScore(int m_tableScore[]);
	

	void introduction(sf::RenderWindow &window);//TODO
	void menu(sf::RenderWindow &window);
	void mapToGame(sf::RenderWindow &window);
	void highScore(sf::RenderWindow &window);
	void enterScore(sf::RenderWindow &window);//TO FINISH
	void gameOver(sf::RenderWindow &window);

	

	sf::Sprite m_screens[NUM_OF_SCREENS];
	sf::Vector2i buttonPos;
	Controller m_gameControl;
	int m_tableScore[NUM_OF_HS];
	void checkSound(); 
	int currentScore;
	bool m_sound;
	int m_screenScore;
	
	void listHs(sf::RenderWindow &window);
	sf::Font font;
	sf::Text listScore[TOP_5];


};

