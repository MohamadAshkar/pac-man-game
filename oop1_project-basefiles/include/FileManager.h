#pragma once

#include "Icon.h"
#include <fstream>
#include <memory>
#include <string>
#include <iostream>
#include <vector>

using std::ifstream;
using std::string;

const int NUM_OF_SOUNDS = 6;
const int NUM_OF_SCREENS = 7;
const int NUM_OF_ICONS = 8;
const int NUM_OF_FONTS = 2;

const int NUM_OF_HS = 5;

struct high_score {
	int score;
	std::string name;
};

class FileManager
{
public:
	sf::Texture * getIconTexture(size_t shape) ;
	sf::Texture * getLifeTexture();
	sf::Font * getFont(size_t type);
	sf::SoundBuffer * getPacmanSound(size_t type);
	sf::SoundBuffer * getGameSound(size_t type);
	static FileManager & instance();
	void updateScore(string, int );

	sf::Texture * getScreen(size_t screen);
	const std::vector<high_score>& loadHighScore();


private:
	FileManager();
	sf::Texture m_pTexture[NUM_OF_ICONS];
	sf::Texture m_pScreeen[NUM_OF_SCREENS];

	sf::Texture m_lifeCount;
	sf::Font m_font[NUM_OF_FONTS];
	sf::SoundBuffer m_pacmanSounds[NUM_OF_SOUNDS-2];
	sf::SoundBuffer m_gameSounds[NUM_OF_SOUNDS - 4];
	
	std::vector<high_score> m_listScore;
};

