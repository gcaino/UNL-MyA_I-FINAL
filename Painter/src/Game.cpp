#include <iostream>
#include "Game.h"
#include "Cannon.h"
#include "PaintBucketsManager.h"

Game::Game()
	: _window()
	, _cannon()
	, _paintBucketsManager()
	, _lives(MAX_LIVES)
	, _score(0)
	, _paused(false)
{
	_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MyA I - TRABAJO FINAL");
	_window->setFramerateLimit(FPS);
	_window->setMouseCursorVisible(false);

	loadTexturesAndSetSprites();
	loadFontsAndSetTexts();

	_cannon = new Cannon();
	_paintBucketsManager = new PaintBucketsManager();
}

Game::~Game()
{
	delete _cannon;
	delete _paintBucketsManager;
	delete _window;
}

void Game::loadTexturesAndSetSprites()
{
	_backgroundTexture.loadFromFile("assets/textures/spr_background.jpg");
	_backgroundSprite.setTexture(_backgroundTexture);

	_crosshairTexture.loadFromFile("assets/textures/crosshair.png");
	_crosshairSprite.setTexture(_crosshairTexture);
	_crosshairSprite.setOrigin(_crosshairSprite.getGlobalBounds().width / 2,
							   _crosshairSprite.getGlobalBounds().height / 2);
	_crosshairSprite.setScale(.5f, .5f);

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

void Game::loadFontsAndSetTexts()
{
	_font.loadFromFile("assets/fonts/PaytoneOne-Regular.ttf");
	_scoreText.setFont(_font);
	_scoreText.setFillColor(sf::Color::White);
	_scoreText.setPosition(_scoreBarSprite.getPosition().x + 10.f, 
		_scoreBarSprite.getPosition().y);
	setScore();
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
			(event.type == sf::Event::KeyPressed && 
				event.key.code == sf::Keyboard::Escape))
		{
			_window->close();
		}
		else if (event.type == sf::Event::KeyPressed && 
			event.key.code == sf::Keyboard::P)
		{
			pause();
		}
		else if (event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Right)
		{
			_cannon->changeColorBall();
		}
		else if (event.type == sf::Event::MouseButtonReleased && 
			event.mouseButton.button == sf::Mouse::Left)
		{
			_cannon->shootBall();
		}
	}
	_cannon->accumulateVelocityXAxis();
}

void Game::pause()
{
	_paused = !_paused;
}

void Game::update(sf::Time deltaTime)
{
	addSpriteToMousePointer();
	_paintBucketsManager->update(deltaTime);
	_paintBucketsManager->checkIfPaintBucketLeftWindow(*_window);
	_cannon->update(deltaTime);
}

void Game::addSpriteToMousePointer()
{
	_crosshairSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window)));
}

void Game::setScore()
{
	_scoreText.setString("Score: " + std::to_string(_score));
}

void Game::draw()
{
	_window->clear();

	_window->draw(_backgroundSprite);
	_cannon->draw(*_window);
	_paintBucketsManager->draw(*_window);
	_window->draw(_scoreBarSprite);
	_window->draw(_scoreText);
	drawLives();
	_window->draw(_crosshairSprite);

	_window->display();
}

void Game::drawLives() const
{
	for (int i = 0; i < _lives; i++)
		_window->draw(_liveSprite[i]);
}


