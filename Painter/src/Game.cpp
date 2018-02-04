#include "Game.h"

Game::Game()
	: _window()
	, _lifes(MAX_LIFES)
	, _score(0)
{
	_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MyA I - TRABAJO FINAL");
	_window->setFramerateLimit(FPS);
}

Game::~Game()
{
	delete _window;
}

void Game::loop()
{
	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;

	while (_window->isOpen())
	{
		processEvents();

		deltaTime = clock.restart();
		update(deltaTime);

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_window->close();
			break;
		default:
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{

}

void Game::render()
{
	_window->clear();

	_window->display();
}
