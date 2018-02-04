#include <iostream>
#include "Game.h"

Game::Game()
	: _window()
	, _lives(MAX_LIVES)
	, _score(0)
	, _paused(false)
{
	_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MyA I - TRABAJO FINAL");
	_window->setFramerateLimit(FPS);

	loadTexturesAndSetSprites();
}

Game::~Game()
{
	delete _window;
}

void Game::loadTexturesAndSetSprites()
{
	_backgroundTexture.loadFromFile("assets/textures/spr_background.jpg");
	_backgroundSprite.setTexture(_backgroundTexture);

	_scoreBarTexture.loadFromFile("assets/textures/spr_scorebar.jpg");
	_scoreBarSprite.setTexture(_scoreBarTexture);
	_scoreBarSprite.setPosition(10.f, 10.f);

	_liveTexture.loadFromFile("assets/textures/spr_lives.png");
	for (int i = 0; i < MAX_LIVES; i++)
	{
		_liveSprite[i].setTexture(_liveTexture);
		_liveSprite[i].setPosition(10.f + (_liveSprite[i].getGlobalBounds().width * i), 
			_scoreBarSprite.getPosition().y + _scoreBarSprite.getGlobalBounds().height + 10.f);
	}
	
	_gameOverTexture.loadFromFile("assets/textures/spr_gameover_click.png");
	_gameOverSprite.setTexture(_gameOverTexture);
}

void Game::loop()
{
	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;

	while (_window->isOpen())
	{
		processEvents();

		deltaTime = clock.restart();
		if (!_paused)
			update(deltaTime);
		
		draw();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			_window->close();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		{
			pause();
		}
	}
}

void Game::pause()
{
	_paused = !_paused;
}

void Game::update(sf::Time deltaTime)
{
	_timer += deltaTime;
	if (_timer >= sf::seconds(5.f))
	{
		--_lives;
		_timer = sf::Time::Zero;
	}
}

void Game::draw()
{
	_window->clear();

	_window->draw(_backgroundSprite);
	_window->draw(_scoreBarSprite);
	drawLives();

	_window->display();
}

void Game::drawLives() const
{
	for (int i = 0; i < _lives; i++)
		_window->draw(_liveSprite[i]);
}


