#include "Screens.h"
#include "Controller.h"
#include "FileManager.h"

// used for saving the screens along the game, and each operates
// updates the screen according the game
Screens::Screens()
	: m_sound(true), m_screenScore(0)
{
	m_tableScore[NUM_OF_HS] = {0};
	m_screens[MENU_m].setTexture(*(FileManager::instance().getScreen(MENU_m)));
	m_screens[MAP_TO_GAME_m].setTexture(*(FileManager::instance().getScreen(MAP_TO_GAME_m)));
	m_screens[HS_m].setTexture(*(FileManager::instance().getScreen(HS_m)));
	m_screens[ENTER_HS_m].setTexture(*(FileManager::instance().getScreen(ENTER_HS_m)));
	m_screens[GAME_OVER_m].setTexture(*(FileManager::instance().getScreen(GAME_OVER_m)));
	m_screens[INTRO_m].setTexture(*(FileManager::instance().getScreen(INTRO_m)));
	m_screens[BACKGROUND_m].setTexture(*(FileManager::instance().getScreen(BACKGROUND_m)));

	m_backroundMusic.openFromFile("backroundMusic.ogg");
	m_backroundMusic.setLoop(true);
	m_backroundMusic.play();

	getUpdatedScore(m_tableScore);
}

Screens::~Screens()
{
}
// creates the main window, and open the game menu
void Screens::runMenu()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(801, 850), "Pacman Game");
	menu(window);
}

// getting buttonof the menu acording the player's choosing,
// and return the choosen one
Menu_t Screens::getMenuButton(sf::Vector2i buttonPos)
{
	if (buttonPos.x > 257 && buttonPos.x < 536 && buttonPos.y > 307 && buttonPos.y < 342)
		return MAP_TO_GAME_t;

	else if (buttonPos.x > 213 && buttonPos.x < 572 && buttonPos.y > 375 && buttonPos.y < 404)
		return INTRO_t;

	else if (buttonPos.x > 239 && buttonPos.x < 563 && buttonPos.y > 443 && buttonPos.y < 477)
		return HS_t;

	else if (buttonPos.x > 339 && buttonPos.x < 454 &&
			 buttonPos.y > 501 && buttonPos.y < 535)
		return EXIT_t;

	else if (buttonPos.x > 732 && buttonPos.x < 773 &&
			 buttonPos.y > 800 && buttonPos.y < 831)
		return SOUND_t;
}
// getting button of the map acording the player's choosing,
// and return the choosen one
MAP_s Screens::getMapButton(sf::Vector2i buttonPos)
{
	if (buttonPos.x > 356 && buttonPos.x < 464 && buttonPos.y > 103 && buttonPos.y < 150)
		return PLAY_s;

	else if (buttonPos.x > 280 && buttonPos.x < 404 && buttonPos.y > 739 && buttonPos.y < 789)
		return MENU_s;

	else if (buttonPos.x > 739 && buttonPos.x < 780 &&
			 buttonPos.y > 800 && buttonPos.y < 831)
		return SOUND_s;
}

// getting button of the enterscore's screen according the player's choosing,
// and return the choosen one
ENTER_HS_h Screens::getEhsButton(sf::Vector2i buttonPos)
{
	if (buttonPos.x > 250 && buttonPos.x < 487 && buttonPos.y > 318 && buttonPos.y < 360)
		return INPUT_h;

	else if (buttonPos.x > 496 && buttonPos.x < 541 && buttonPos.y > 319 && buttonPos.y < 358)
		return OK_h;

	else if (buttonPos.x > 336 && buttonPos.x < 458 && buttonPos.y > 802 && buttonPos.y < 825)
		return MENU_h;

	else if (buttonPos.x > 721 && buttonPos.x < 762 && buttonPos.y > 795 && buttonPos.y < 826)
		return SOUND_h;
}
// getting button of the high score's screen according the player's choosing,
// and return the choosen one
HS_v Screens::getHsButton(sf::Vector2i buttonPos)
{
	if (buttonPos.x > 335 && buttonPos.x < 461 && buttonPos.y > 804 && buttonPos.y < 824)
		return MENU_v;

	else if (buttonPos.x > 735 && buttonPos.x < 777 && buttonPos.y > 798 && buttonPos.y < 832)
		return SOUND_v;
}
// getting button of the game over's screen according the player's choosing,
// and return the choosen one
GAME_OVER_f Screens::getGoButton(sf::Vector2i buttonPos)
{
	if (buttonPos.x > 247 && buttonPos.x < 536 && buttonPos.y > 180 && buttonPos.y < 202)
		return HS_f;

	else if (buttonPos.x > 299 && buttonPos.x < 479 && buttonPos.y > 375 && buttonPos.y < 395)
		return PLAY_f;

	else if (buttonPos.x > 360 && buttonPos.x < 438 && buttonPos.y > 805 && buttonPos.y < 823)
		return MENU_f;

	else if (buttonPos.x > 738 && buttonPos.x < 779 && buttonPos.y > 802 && buttonPos.y < 831)
		return SOUND_f;
}
// getting button of the game insructions's screen according the player's choosing,
// and return the choosen one
INTRO_a Screens::getIntrButton(sf::Vector2i buttonPos)
{
	if (buttonPos.x > 359 && buttonPos.x < 437 && buttonPos.y > 805 && buttonPos.y < 824)
		return MENU_a;

	else if (buttonPos.x > 732 && buttonPos.x < 772 && buttonPos.y > 753 && buttonPos.y < 831)
		return SOUND_a;
}
// used for updating the table score
void Screens::getUpdatedScore(int m_tableScore[])
{
	auto score = FileManager::instance().loadHighScore();
	for (int i = 0; i < TOP_5; i++)
		m_tableScore[i] = score[i].score;
}

// while the plyer choosed this screen,
// he can choose the next step by the buttons
// exept that, prints the introduction's screen
void Screens::introduction(sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();

				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					INTRO_a button = getIntrButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					switch (button)
					{
					case MENU_a: // go back to menu
						menu(window);
						break;
						// turn on/off music
					case SOUND_a:
						checkSound();
						break;
					}
				}
			}
		}
		window.draw(m_screens[INTRO_m]);
		window.display();
		window.clear();
	}
}

// while the plyer choosed this screen,
// he can choose the next step by the buttons
// exept that, prints the menu's screen
void Screens::menu(sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Menu_t button = getMenuButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					switch (button)
					{
					case MAP_TO_GAME_t: // go the the game map
						mapToGame(window);
						break;

					case HS_t:
						highScore(window); // go the the high score
						break;

					case INTRO_t:
						introduction(window); // go to introduction
						break;

					case EXIT_t:
						window.close(); // exit the game
						break;

					case SOUND_t:
						checkSound(); // turn on/off music
						break;

					default:
						break;
					}
				}
				break;
			}
		}
		window.draw(m_screens[MENU_m]); // draw the menu's screen
		window.display();
		window.clear();
	}
}

// while the plyer choosed this screen,
// he can choose the next step by the buttons
// exept that, prints the map to game's screen
void Screens::mapToGame(sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					MAP_s button = getMapButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					switch (button)
					{
					case PLAY_s:
					{
						bool close = true;
						int i; // calls the controller and start playing
						// window.draw(m_screens[BACKGROUND_m]);
						if (m_gameControl.run(window, m_tableScore, m_backroundMusic, i))
						{

							// if the player got higher number than the table
							//  enter the score to the table
							m_screenScore = m_tableScore[i];
							window.create(sf::VideoMode(801, 850), "Pacman Game");
							enterScore(window);
						}

						else
						{
							if (!close)
								window.close();

							window.create(sf::VideoMode(801, 850), "Pacman Game");
							gameOver(window); // else  go to game over
						}
					}
					break;

					case MENU_s: // go to menu
						menu(window);
						break;

					case SOUND_s: // turn on/off music
						checkSound();
						break;
					}
				}
			}
		}
		window.draw(m_screens[MAP_TO_GAME_m]);
		window.display();
		window.clear();
	}
}

// while the plyer choosed this screen,
// he can choose the next step by the buttons
// exept that, prints table score's screen
void Screens::highScore(sf::RenderWindow &window)
{
	if (!font.loadFromFile("Latinia.ttf"))
	{
		std::cout << "error font";
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					HS_v button = getHsButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					switch (button)
					{
					case MENU_v: // back to menu
						menu(window);
						break;

					case SOUND_v: // turn on/off music
						checkSound();
						break;
					}
				}
			}
		}

		// draw the table score ont the high score's screen
		auto score = FileManager::instance().loadHighScore();
		window.draw(m_screens[HS_m]);
		for (int i = 0; i < TOP_5; i++)
		{
			listScore[i].setFont(font);
			listScore[i].setString(score[i].name);

			listScore[i].setCharacterSize(30);
			listScore[i].setFillColor(sf::Color::Blue);
			listScore[i].setPosition({200.f, 321.f + 50 * i});
			window.draw(listScore[i]);

			listScore[i].setString(std::to_string(score[i].score));
			listScore[i].setCharacterSize(30);
			listScore[i].setFillColor(sf::Color::Blue);
			listScore[i].setPosition({483.f, 321.f + 50 * i});
			m_tableScore[i] = score[i].score;
			window.draw(listScore[i]);
		}

		window.display();
		window.clear();
	}
}

// while the plyer got bigger score than the table now,
// the player writes his name, and continue to seee it in
// the high score's screen
void Screens::enterScore(sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					ENTER_HS_h button = getEhsButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					switch (button)
					{
					case MENU_h:
						menu(window);
						break;

					case INPUT_h:
					{
						listHs(window);
						break;
					}
					case OK_h:
						highScore(window);
						break;

					case SOUND_h:
						checkSound();
						break;
					}
				}
			}
		}
		window.draw(m_screens[ENTER_HS_m]);
		window.display();
		window.clear();
	}
}

// if the player got low score , he gots this screen
// of "game over"
void Screens::gameOver(sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					GAME_OVER_f button = getGoButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					switch (button)
					{
					case MENU_f:
						menu(window);
						break;

					case PLAY_f:
						int i;
						if (m_gameControl.run(window, m_tableScore, m_backroundMusic, i))
						{
							m_screenScore = m_tableScore[i];
							window.create(sf::VideoMode(801, 850), "Pacman Game");
							enterScore(window);
						}
						else
						{
							window.create(sf::VideoMode(801, 850), "Pacman Game");
							gameOver(window);
						}

						break;

					case HS_f:
						highScore(window);
						break;

					case SOUND_f:
						checkSound();
						break;
					}
				}
			}
		}
		window.draw(m_screens[GAME_OVER_m]);
		window.display();
		window.clear();
	}
}

// if the player got high score, he writes this
// in this function
void Screens::listHs(sf::RenderWindow &window)
{
	if (!font.loadFromFile("Latinia.ttf"))
	{
		std::cout << "error font";
	}
	sf::String sentence;
	sf::Text text(sentence, font, 25);
	text.setFillColor(sf::Color(44, 127, 255));
	text.setPosition(258, 324);
	text.setStyle(sf::Text::Bold);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			case sf::Event::TextEntered:
			{
				if (sentence.getSize() <= 10)
				{
					if (event.text.unicode >= 32 && event.text.unicode <= 126)
						sentence += (char)event.text.unicode;
					else if (event.text.unicode == 8 && sentence.getSize() > 0)
						sentence.erase(sentence.getSize() - 1, sentence.getSize());

					text.setString(sentence);
				}
				break;
			}

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					ENTER_HS_h button = getEhsButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					switch (button)
					{
					case OK_h:
					{
						FileManager::instance().updateScore(sentence, m_screenScore);
						highScore(window);
					}
					break;
					case MENU_h:
						menu(window);
						break;
					case SOUND_h:
						checkSound();
						break;
					default:
						break;
					}
				}
				break;
			}
		}
		window.draw(m_screens[ENTER_HS_m]);
		window.draw(text);
		window.display();
		window.clear();
	}
}

// a function thatss used for updating the sound's status
// if the sound is off, after pushing the button the sound is on.
// else do the opposite
void Screens::checkSound()
{
	if (!m_sound)
	{
		m_backroundMusic.setVolume(100);
		m_sound = true;
	}

	else
	{
		m_backroundMusic.setVolume(0);
		m_sound = false;
	}
}
