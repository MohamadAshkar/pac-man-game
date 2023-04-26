#pragma once

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include "FileManager.h"
#include <vector>

using std::vector;




class Pacman;
class Wall;
class Demon;
class Cookie;
class Level;
class RandomDemon;
class SmartDemon;
class Door;
class Key;
class Gift;
class Superpacman;


enum Color_t { RED, GREEN, BLUE };
enum Object_t { PACMAN, DEMON, COOKIE, WALL, KEY, DOOR, GIFT, SUPERPACMAN }; 
enum PacmanSound_t {MUNCH, DEATH, HEALTH_COOKIE, POISON_COOKIE};
enum gameSound_t {LVL_UP, GAME_IS_OVER };

enum Screen_m {MENU_m, MAP_TO_GAME_m, HS_m, ENTER_HS_m, GAME_OVER_m, INTRO_m, BACKGROUND_m};
enum Menu_t {MAP_TO_GAME_t, HS_t, EXIT_t, SOUND_t, INTRO_t};
enum MAP_s { PLAY_s, MENU_s, SOUND_s};
enum INTRO_a { MENU_a, SOUND_a};
enum ENTER_HS_h {MENU_h, INPUT_h, OK_h, SOUND_h};
enum HS_v {MENU_v, SOUND_v};
enum GAME_OVER_f {MENU_f, PLAY_f, HS_f, SOUND_f};

enum Fonts_t {GAME_FONT, GET_READY_FONT};

const int P_SIZE = 32; //cell size
const int NUM_OF_SCORES = 5;
const int SCORE_COOKIE = 2;
const int SCORE_KEY = 7;
const int SCORE_GIFT = 5;
const int SCORE_LEVEL = 50;
const int SCORE_DEMON = 2;


class Icon
{
public:
	Icon() {};
	~Icon() {};
	//defines collisions of the objects
	virtual void collide(Icon * object, Level & m_level) = 0;
	virtual void collide(Pacman * object, Level & m_level) = 0 ;
	virtual void collide(Demon * object, Level & m_level) = 0;
	virtual void collide(Cookie * object, Level & m_level) = 0;
	virtual void collide(Wall * object, Level & m_level) = 0;
	virtual void collide(Door* object, Level& m_level) = 0;
	virtual void collide(Key* object, Level& m_level) = 0;
	virtual void collide(Gift* object, Level& m_level) = 0;
	virtual void collide(Superpacman* object, Level& m_level) = 0;
	
	

protected:
	Object_t m_type;
	sf::Sprite m_sprite;
	
	

};

