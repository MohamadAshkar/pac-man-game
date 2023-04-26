#include "Controller.h"

Controller::Controller() : m_pacman(), m_demons(), m_level(m_pacman, m_demons, m_levelNumber)
{
	srand((unsigned)time(NULL));
	m_sound[LVL_UP].setBuffer(*(FileManager::instance().getGameSound(LVL_UP)));
	m_sound[GAME_IS_OVER].setBuffer(*(FileManager::instance().getGameSound(GAME_IS_OVER)));
	m_font = *(FileManager::instance().getFont(GET_READY_FONT));
	m_getReady.setFont(m_font);
}

Controller::~Controller()
{
	m_level.clear_vector();
}

// run function - runs the game
//
//
bool Controller::run(sf::RenderWindow &window, int highScores[], sf::Music &backroundMusic, int &i)
{
	window.create(sf::VideoMode(m_level.getBoardSize().y, m_level.getBoardSize().x + 50), "Pacman Game");
	window.setKeyRepeatEnabled(false);
	PlayerStates statesBar;
	static sf::Clock clock;
	bool isMoving = false;
	m_pacman.setScore(-m_pacman.getScore());

	while (window.isOpen())
	{
		drawGetReady(window);
		window.display();
		static sf::Clock timer;
		timer.restart();
		static sf::Time two_min = sf::seconds(150);

		while (!isOver())
		{
			m_curr_time = two_min.asSeconds() - timer.getElapsedTime().asSeconds() + m_pacman.getAddTime();
			if (m_curr_time == 0)
			{
				break;
			}

			if (levelFinished())
			{
				m_levelNumber++;
				if (m_levelNumber <= NUM_OF_LEVELS)
				{
					m_pacman.setKey(false);
					levelUp(isMoving, window);
					timer.restart();
				}
				else
					break;
			}
			bool close = true;
			sf::Event Event;
			while (window.pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed:
					close = false;

					break;
				default:
					checkEvent(window, clock, Event, isMoving, backroundMusic);
				}
			}
			if (!close)
				break;

			float passedTime = clock.restart().asSeconds();
			moveDynamic(window, passedTime, isMoving);
			draw(window, passedTime, m_curr_time);
			window.display();
			window.clear();
		}
		m_sound[GAME_IS_OVER].play();

		break;
	}
	resetGame(window, isMoving);
	return checkForHs(highScores, m_pacman.getScore(), i);
}

void Controller::checkCollision(DynamicIcon *character, Direction_t direction)
{
	Icon *icon = m_level.getIcon(character->getNextDirection(direction));
	if (icon != nullptr)
		icon->collide(character, m_level);
}

// a function thats sets the direction of the pacman

void Controller::setDirection(sf::Event newEvent, bool &isMoving, sf::Clock &clock)
{
	if (newEvent.key.code == sf::Keyboard::Space)
		isMoving = false;
	if (newEvent.key.code == sf::Keyboard::Left || newEvent.key.code == sf::Keyboard::Up ||
		newEvent.key.code == sf::Keyboard::Down || newEvent.key.code == sf::Keyboard::Right)
	{
		setPacmanDirection(newEvent.key.code);
		isMoving = true;
		clock.restart().asSeconds();
	}
}

// a function thats moves the pacman and the demons
void Controller::moveDynamic(sf::RenderWindow &window, float passedTime, bool &isMoving)
{
	vector<std::vector<sf::Vector3i>> Tree;
	if (isMoving)
	{
		m_pacman.move(passedTime, m_level.getBoardSize());
		checkCollision(&m_pacman, m_pacman.getDirection());
	}
	if (m_pacman.getPacmanState())
	{
		setDynamics(window, isMoving);
		drawGetReady(window);
	}
	Tree = getBfsTree(sf::Vector2i((int)(m_pacman.getPosition().x / P_SIZE),
								   (int)(m_pacman.getPosition().y / P_SIZE)),
					  m_level.getBoard());

	if (m_pacman.getStopDemon())
	{
		if (m_pacman.stopDemonTimer() <= 0)
			m_pacman.setStop(false);
	}
	else
	{
		for (size_t i = 0; i < m_demons.size(); i++)
		{
			m_demons[i]->move(passedTime, m_level.getBoardSize(), Tree);
			checkCollision(m_demons[i].get(), m_demons[i].get()->getDirection());
			if (atePacman(m_demons[i].get()))
				m_pacman.collide(m_demons[i].get(), m_level);
		}
	}
}

void Controller::set_Level_value(const int value)
{
	m_levelNumber = value;
}

void Controller::setPacmanDirection(sf::Keyboard::Key direction)
{
	m_pacman.setDirection(direction);
}
// a function thats resets all the game stats
void Controller::resetGame(sf::RenderWindow &window, bool &isMoving)
{
	m_pacman.setLife(3);
	size_t size = m_demons.size();

	for (size_t i = 0; i < size; i++)
		m_demons.pop_back();
	m_level.clear_vector();
	set_Level_value(1);
	m_pacman.setCookieCounter(-m_pacman.getCookies());
	m_pacman.setKey(false);
	m_level.read_level(m_pacman, m_demons, m_levelNumber);
	isMoving = false;
}

// a function thats checks the events in the game

void Controller::checkEvent(sf::RenderWindow &window, sf::Clock &clock, sf::Event Event, bool &isMoving, sf::Music &backroundMusic)
{
	switch (Event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyPressed:
		switch (Event.key.code)
		{
		case sf::Keyboard::O:
			backroundMusic.setVolume(backroundMusic.getVolume() + 10);
			break;
		case sf::Keyboard::P:
			backroundMusic.setVolume(backroundMusic.getVolume() - 10);
			break;
		case sf::Keyboard::S:
			mute(backroundMusic);
			break;
		}
		setDirection(Event, isMoving, clock);
		break;
	}
}

// a function thats checks if the player got a high score
bool Controller::checkForHs(int highScores[], int score, int &index)
{
	for (int i = 0; i < NUM_OF_SCORES; i++)
	{
		if (score > highScores[i])
		{
			highScores[i] = score;
			index = i;
			return true;
		}
	}
	return false;
}

// a function thats toggles the backround music
void Controller::mute(sf::Music &backroundMusic)
{
	if (m_mute)
	{
		backroundMusic.setVolume(100);
		m_mute = false;
	}
	else
	{
		backroundMusic.setVolume(0);
		m_mute = true;
	}
}

// a function thats draws the "GET READY!" sign

void Controller::drawGetReady(sf::RenderWindow &window)
{
	std::string getReady;
	float time = 0;
	sf::Clock clock;
	clock.restart();
	m_getReady.setCharacterSize(P_SIZE);
	m_getReady.setOutlineColor(sf::Color::Black);
	m_getReady.setOutlineThickness(3);
	for (int i = 0; i < 3;)
	{
		getReady = "GET READY!  " + std::to_string(3 - i);
		time += clock.getElapsedTime().asSeconds();
		draw(window, 0, 0);
		m_getReady.setPosition(m_level.getBoardSize().y / 2 - 70, m_level.getBoardSize().x / 2);
		m_getReady.setString(getReady);
		window.draw(m_getReady);
		window.display();
		window.clear();
		if (time >= 5)
		{
			i++;
			time = 0;
			clock.restart();
		}
	}
}

// a function thats draws the pacman , the demons and the board
void Controller::draw(sf::RenderWindow &window, float passedTime, int curr_time)
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background.jpg");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);
	window.draw(backgroundSprite);
	m_level.drawStatic(window);
	m_statesBar.draw(window, m_pacman.getLife(), m_pacman.getScore(), m_levelNumber, curr_time, m_level.getBoardSize());
	drawDynamic(window, passedTime);
}

// a function thats checks if all the blue cookies were eaten
bool Controller::levelFinished()
{
	return m_pacman.getCookies() <= 0;
}

// a function thats returns the bfs tree from the pacman position
vector<std::vector<sf::Vector3i>> Controller::getBfsTree(sf::Vector2i start, const vector<vector<std::unique_ptr<StaticIcon>>> &board)
{
	vector<std::vector<sf::Vector3i>> Tree;
	Tree.assign(board.size(), std::vector<sf::Vector3i>(board[0].size(),
														sf::Vector3i(INT_MAX, -1, -1)));

	Tree[start.y][start.x].x = 0;

	// set a queue to hold cordinate
	std::queue<sf::Vector2i> que;

	// put cordinate in the queue
	que.push(start);

	// chek if the queue is empty
	while (!que.empty())
	{
		// take a cordinate from the queue
		sf::Vector2i current = que.front();
		que.pop();

		// set a vector of all the legal neighboors
		std::vector<sf::Vector2i> neighbors = getNeighbors(current, board);

		// check all the neighbors and set them ways
		for (unsigned int i = 0; i < neighbors.size(); i++)
		{
			// set next and check it
			sf::Vector2i next = neighbors[i];

			// if its a good neighbor, set his way
			if ((next.y != start.y || next.x != start.x) &&
				Tree[next.y][next.x].x == INT_MAX)
			{
				que.push(next);
				Tree[next.y][next.x].x = Tree[current.y][current.x].x + 1;
				Tree[next.y][next.x].y = current.x;
				Tree[next.y][next.x].z = current.y;
			}
		}
	}

	// return the bfs that was faund
	return Tree;
}

// a function thats returns the nieghbors of a certain cell in the board
vector<sf::Vector2i> Controller::getNeighbors(const sf::Vector2i center,
											  const vector<vector<std::unique_ptr<StaticIcon>>> &board)
{
	std::vector<sf::Vector2i> shifts = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	// set vector to hold the result
	std::vector<sf::Vector2i> neighbors;

	sf::Vector2i next;

	for (int i = 0; i < 4; i++)
	{
		next = center + shifts[i];

		if (OutOfBoard((sf::Vector2f)next, board) &&
			!dynamic_cast<Wall *>(board[next.y][next.x].get()))
			neighbors.push_back(next);
	}

	// return the neighbors
	return neighbors;
}

// a function thatss checks if a certain cell is out of the board
bool Controller::OutOfBoard(sf::Vector2f place, const vector<vector<std::unique_ptr<StaticIcon>>> &board)
{
	return !(place.x < 0 || place.y < 0 || place.x >= board[0].size() ||
			 place.y >= board.size());
}

// a function thats sets the next level's board , pacman and demons positions
void Controller::levelUp(bool &isMoving, sf::RenderWindow &window)
{
	m_sound[0].play();
	size_t size = m_demons.size();
	for (size_t i = 0; i < size; i++)
		m_demons.pop_back();
	m_level.clear_vector();
	m_level.read_level(m_pacman, m_demons, m_levelNumber);
	isMoving = false;
	window.create(sf::VideoMode(m_level.getBoardSize().y, m_level.getBoardSize().x + 50), "Pacman Game");
	drawGetReady(window);
}

// a function thats checks if pacman was eaten
bool Controller::atePacman(Demon *demon)
{
	return (abs(m_pacman.getPosition().x - demon->getPosition().x) < P_SIZE &&
			abs(m_pacman.getPosition().y - demon->getPosition().y) < P_SIZE);
}

// a function thats sets the pacman and demons positions
void Controller::setDynamics(sf::RenderWindow &window, bool &isMoving)
{
	m_pacman.SetPosition(m_pacman.getStartingPosition());
	for (size_t i = 0; i < m_demons.size(); i++)
		m_demons[i]->SetPosition(m_demons[i]->getStartingPosition());
	m_pacman.setPacmanState();
	isMoving = false;
}

// a function thats checks if game is over
bool Controller::isOver()
{
	return (m_pacman.getLife() <= 0);
}

// a function thats draws the pacman and the demons
void Controller::drawDynamic(sf::RenderWindow &window, float passedTime)
{
	if (m_pacman.getSuper())
	{
		if (m_pacman.getSuperPacmanTimer() <= 0)
		{
			m_level.setPacman(m_pacman, GREEN, m_pacman.getPosition());
			m_pacman.setSuper(false);
			m_pacman.setKey(false);
		}
	}
	m_pacman.draw(window, passedTime);
	for (size_t i = 0; i < m_demons.size(); i++)
		m_demons[i]->draw(window, passedTime);
}
