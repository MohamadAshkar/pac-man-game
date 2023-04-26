#include "FileManager.h"

// The file manager consructor - the singeltone!
//  used for loading all the critic files, as sounds, imaegs
//  and screens.
//  this is the singeltone class
FileManager::FileManager()
{
	// loading images
	m_pTexture[PACMAN].loadFromFile("pacman.png");
	m_pTexture[DEMON].loadFromFile("demon.png");
	m_pTexture[COOKIE].loadFromFile("cookie.png");
	m_pTexture[WALL].loadFromFile("wall.png");
	m_pTexture[DOOR].loadFromFile("door.png");
	m_pTexture[KEY].loadFromFile("key.png");
	m_pTexture[GIFT].loadFromFile("gift.png");
	m_pTexture[SUPERPACMAN].loadFromFile("treasure.png");

	//  loading screens
	m_pScreeen[MENU_m].loadFromFile("menu.jpg");
	m_pScreeen[HS_m].loadFromFile("high_score.jpg");
	m_pScreeen[ENTER_HS_m].loadFromFile("write_score.jpg");
	m_pScreeen[MAP_TO_GAME_m].loadFromFile("map_to_game.jpg");
	m_pScreeen[GAME_OVER_m].loadFromFile("game_is_over.jpg");
	m_pScreeen[INTRO_m].loadFromFile("instruction.jpg");
	m_pScreeen[BACKGROUND_m].loadFromFile("background.jpg");

	// loading sounds

	m_lifeCount.loadFromFile("life.png");
	m_font[GAME_FONT].loadFromFile("gameFont.otf");
	m_font[GET_READY_FONT].loadFromFile("getReadyFont.otf");
	m_pacmanSounds[MUNCH].loadFromFile("munch.wav");
	m_pacmanSounds[DEATH].loadFromFile("death.wav");
	m_gameSounds[LVL_UP].loadFromFile("lvl_up.wav");
	m_gameSounds[GAME_IS_OVER].loadFromFile("game_over.wav");
	m_pacmanSounds[HEALTH_COOKIE].loadFromFile("health_cookie.wav");
	m_pacmanSounds[POISON_COOKIE].loadFromFile("poison_cookie.wav");
}
// a function thatss gets icon texture and return the shpe
sf::Texture *FileManager::getIconTexture(size_t shape)
{
	return &m_pTexture[shape];
}
// a function thats used for returning the life's counter
sf::Texture *FileManager::getLifeTexture()
{
	return &m_lifeCount;
}
// a function thats used for getting and return the fonts
sf::Font *FileManager::getFont(size_t type)
{
	return &m_font[type];
}
// a function thats used for getting the sounds for the pacman
// along the game
sf::SoundBuffer *FileManager::getPacmanSound(size_t type)
{
	return &m_pacmanSounds[type];
}
// a function thats used for getting the sounds for the game
// sounds as eating cookies, dead etc.
sf::SoundBuffer *FileManager::getGameSound(size_t type)
{
	return &m_gameSounds[type];
}
// a function thats used for getting the sounds for the game
FileManager &FileManager::instance()
{
	static FileManager instance;
	return instance;
}
// a function thats used for updating file who containes
// the high score
void FileManager::updateScore(string name, int score)
{
	auto highScore = loadHighScore();

	highScore.push_back(high_score{score, name});
	std::sort(highScore.begin(), highScore.end(), [&](high_score i, high_score j)
			  { return (i.score > j.score); });

	string file = "highScore.txt";
	std::ofstream output;
	output.open(file);
	output.clear();

	for (int i = 0; i < 5 && i < highScore.size(); i++)
	{
		output << highScore[i].name << "\n"
			   << highScore[i].score;
		if (i < 4 && i < highScore.size() - 1)
			output << "\n";
	}
	output.close();
}
// a function thats used for getting screens, along the program
sf::Texture *FileManager::getScreen(size_t screen)
{
	return &m_pScreeen[screen];
}
// a function thats used for getting the files who
// containes the high score
const std::vector<high_score> &FileManager::loadHighScore()
{

	string file = "highScore.txt";
	ifstream input_score;
	input_score.open(file);
	if (!input_score.is_open())
	{
		std::cerr << "could not open file\n";
		exit(EXIT_FAILURE);
	}

	m_listScore.clear();
	while (!input_score.eof())
	{
		m_listScore.push_back(high_score());
		input_score >> m_listScore.back().name;
		input_score >> m_listScore.back().score;
	}
	input_score.close();
	return m_listScore;
}
