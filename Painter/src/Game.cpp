#include <iostream>
#include <vector>
#include "Game.h"
#include "Cannon.h"
#include "Ball.h"
#include "PaintBucketsManager.h"
#include "PaintBucket.h"

Game::Game()
	: _window()
	, _cannon()
	, _paintBucketsManager()
	, _lives(MAX_LIVES)
	, _score(0)
	, _accumulatedScoreToGainLife(0)
	, _paused(false)
	, _currentState(STATE::MENU)
{
	_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MyA I - TRABAJO FINAL");
	_window->setFramerateLimit(FPS);
	_window->setMouseCursorVisible(false);

	loadTexturesAndSetSprites();
	loadFontsAndSetTexts();
	loadSoundBuffersAndSetSounds();
	
	_cannon = new Cannon(this);
	_paintBucketsManager = new PaintBucketsManager(this, MAX_PAINT_BUCKETS);
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

	_menuScreenTexture.loadFromFile("assets/textures/spr_menu_screen_b.jpg");
	_menuScreenSprite.setTexture(_menuScreenTexture);

	_instructionsTexture.loadFromFile("assets/textures/spr_instructions_screen.jpg");
	_instructionsSprite.setTexture(_instructionsTexture);

	_crosshairTexture.loadFromFile("assets/textures/brush.png");
	_crosshairSprite.setTexture(_crosshairTexture);
	_crosshairSprite.setOrigin(_crosshairSprite.getGlobalBounds().width / 2,
							   _crosshairSprite.getGlobalBounds().height / 2);
	_crosshairSprite.setScale(.35f, .35f);

	_barTexture.loadFromFile("assets/textures/spr_scorebar.jpg");
	_scoreSpriteBar.setTexture(_barTexture);
	_scoreSpriteBar.setPosition(10.f, 10.f);

	_powerSpriteBar.setTexture(_barTexture);
	_powerSpriteBar.setPosition(_scoreSpriteBar.getPosition().x + _scoreSpriteBar.getGlobalBounds().width + 10.f, 10.f);
	_powerSpriteBar.setScale(1.15f, 1.f);

	_liveTexture.loadFromFile("assets/textures/spr_lives.png");
	for (int i = 0; i < MAX_LIVES; i++)
	{
		_liveSprite[i].setTexture(_liveTexture);
		_liveSprite[i].setPosition(10.f + (_liveSprite[i].getGlobalBounds().width * i), 
			_scoreSpriteBar.getPosition().y + _scoreSpriteBar.getGlobalBounds().height + 10.f);
	}
	
	_gameOverTexture.loadFromFile("assets/textures/spr_gameover_enter.png");
	_gameOverSprite.setTexture(_gameOverTexture);
	_gameOverSprite.setOrigin(_gameOverSprite.getGlobalBounds().width / 2, _gameOverSprite.getGlobalBounds().height / 2);
	_gameOverSprite.setPosition(static_cast<float>(_window->getSize().x) / 2, static_cast<float>(_window->getSize().y / 2));

	_buttonClickSoundBuffer.loadFromFile("assets/audio/snd_button_click.ogg");
	_buttonClickSound.setBuffer(_buttonClickSoundBuffer);
}

void Game::loadFontsAndSetTexts()
{
	_font.loadFromFile("assets/fonts/PaytoneOne-Regular.ttf");

	_scoreText.setFont(_font);
	_scoreText.setFillColor(sf::Color::White);
	_scoreText.setPosition(_scoreSpriteBar.getPosition().x + 10.f, 
		_scoreSpriteBar.getPosition().y);

	_powerText.setFont(_font);
	_powerText.setFillColor(sf::Color::Red);
	_powerText.setPosition(_powerSpriteBar.getPosition().x + 10.f,
		_powerSpriteBar.getPosition().y);

	updateScoreBar();
}

void Game::loadSoundBuffersAndSetSounds()
{
	_bubblePopSoundBuffer.loadFromFile("assets/audio/snd_bubble_pop.ogg");
	_bubblePopSound.setBuffer(_bubblePopSoundBuffer);
	_balloonExplodesSoundBuffer.loadFromFile("assets/audio/snd_balloon_explode.ogg");
	_balloonExplodesSound.setBuffer(_balloonExplodesSoundBuffer);

	_music.openFromFile("assets/audio/snd_circus_music.ogg");
	_music.setVolume(40.f);
	_music.setLoop(true);
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

		switch (_currentState)
		{
		case STATE::MENU:
			checkIfStart(event);
			break;
		case STATE::INSTRUCTIONS:
			checkIfPlay(event);
			break;
		case STATE::GAMEPLAY:
			_cannon->processEvents(event);
			break;
		case STATE::GAMEOVER:
			checkIfStartAgain(event);
			break;
		default:
			break;
		}
	}

	if (_currentState == STATE::GAMEPLAY)
		_cannon->accumulatePower();
}

void Game::pause()
{
	_paused = !_paused;

	if (_music.getStatus() == sf::Music::Playing)
		_music.pause();
	else
		_music.play();
}

void Game::checkIfStart(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		_currentState = STATE::INSTRUCTIONS;
		_buttonClickSound.play();
	}
}

void Game::checkIfPlay(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		_currentState = STATE::GAMEPLAY;
		_buttonClickSound.play();
		_music.play();
	}
}

void Game::update(sf::Time deltaTime)
{
	addSpriteToMousePointer();

	if (_currentState == STATE::GAMEPLAY)
	{
		_paintBucketsManager->update(deltaTime);
		_paintBucketsManager->checkIfPaintBucketLeftWindow(*_window);
		_cannon->update(deltaTime);
		updatePowerBar();
		checkCollisions();
		checkIfBallLeftWindow();
		checkIfLifeIncreases();
		checkDefeatCondition();
	}
}

void Game::addSpriteToMousePointer()
{
	_crosshairSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window)));
}

void Game::updateScoreBar()
{
	_scoreText.setString("Score: " + std::to_string(_score));
}

void Game::updatePowerBar()
{
	_powerText.setString("Power: " + std::to_string(static_cast<int>(_cannon->getPower())));
}

void Game::checkCollisions()
{
	if (_cannon->getBalls().empty())
		return;

	std::vector<Ball*> balls = _cannon->getBalls();
	std::vector<PaintBucket*> paintBuckets = _paintBucketsManager->getPaintBuckets();
	int maxPaintBuckets = _paintBucketsManager->getPaintBuckets().size();
	for (size_t i = 0; i < balls.size(); i++)
	{
		if (balls[i]->isActive())
		{
			for (int j = 0; j < maxPaintBuckets; j++)
			{
				if (balls[i]->getSprite().getGlobalBounds().intersects(paintBuckets[j]->getSprite().getGlobalBounds()))
				{
					_bubblePopSound.play();
					balls[i]->setActive(false);
					paintBuckets[j]->getSprite().setTexture(_paintBucketsManager->getPaintBucketTexturesByColor(balls[i]->getColor()));
					paintBuckets[j]->setColor(balls[i]->getColor());
				}
			}
		}
	}
}

void Game::updateScore()
{
	_score += SCORE_POINTS;
	_accumulatedScoreToGainLife += SCORE_POINTS;
	updateScoreBar();
}

void Game::decreaseLifeByOne()
{
	--_lives;
	_balloonExplodesSound.play();
}

void Game::checkIfBallLeftWindow()
{
	std::vector<Ball*> balls = _cannon->getBalls();
	int totalBalls = _cannon->getBalls().size();
	for (int i = 0; i < totalBalls; i++)
	{
		if (balls[i]->isActive())
		{
			if (balls[i]->getSprite().getPosition().x > _window->getSize().x ||
				balls[i]->getSprite().getPosition().x < 0 ||
				balls[i]->getSprite().getPosition().y > _window->getSize().y ||
				balls[i]->getSprite().getPosition().y < 0)
			{
				balls[i]->setActive(false);
			}
		}
	}
}

void Game::checkIfLifeIncreases()
{
	if (_accumulatedScoreToGainLife >= BASE_SCORE_POINTS_TO_GAIN_LIFE &&
		_lives < MAX_LIVES)
	{
		++_lives;
		_accumulatedScoreToGainLife -= BASE_SCORE_POINTS_TO_GAIN_LIFE;
	}
}

void Game::checkDefeatCondition()
{
	if (_lives <= 0)
	{
		_currentState = STATE::GAMEOVER;
		_music.stop();
	}
}

void Game::checkIfStartAgain(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased &&
		event.key.code == sf::Keyboard::Return)
	{
		_buttonClickSound.play();
		reset();
	}
}

void Game::reset()
{
	_score = 0;
	_accumulatedScoreToGainLife = 0;
	updateScoreBar();
	_lives = MAX_LIVES;
	drawLives();
	_cannon->setPowerToBase();
	_paintBucketsManager->reset();
	_cannon->reset();
	_currentState = STATE::GAMEPLAY;
	_music.play();
}

void Game::draw()
{
	_window->clear();

	switch (_currentState)
	{
	case STATE::MENU:
		_window->draw(_menuScreenSprite);
		break;
	case STATE::INSTRUCTIONS:
		_window->draw(_instructionsSprite);
		break;
	case STATE::GAMEPLAY:
		_window->draw(_backgroundSprite);
		_paintBucketsManager->draw(*_window);
		_cannon->draw(*_window);
		_window->draw(_scoreSpriteBar);
		_window->draw(_powerSpriteBar);
		_window->draw(_scoreText);
		_window->draw(_powerText);
		drawLives();
		break;
	case STATE::GAMEOVER:
		_window->draw(_backgroundSprite);
		_cannon->draw(*_window);
		_window->draw(_scoreSpriteBar);
		_window->draw(_scoreText);
		_window->draw(_gameOverSprite);
		break;
	default:
		break;
	}
	_window->draw(_crosshairSprite);

	_window->display();
}

void Game::drawLives() const
{
	for (int i = 0; i < _lives; i++)
		_window->draw(_liveSprite[i]);
}


