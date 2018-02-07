#include <iostream>
#include "PaintBucketsManager.h"
#include "Game.h"
#include "PaintBucket.h"
#include "enums.h"

PaintBucketsManager::PaintBucketsManager(Game* game)
	: _game(game)
	, _spawningTime(sf::seconds(0.f))
{
	_paintBucketTextures[Utils::COLORS::BLUE].loadFromFile("assets/textures/spr_can_blue.png");
	_paintBucketTextures[Utils::COLORS::RED].loadFromFile("assets/textures/spr_can_red.png");
	_paintBucketTextures[Utils::COLORS::GREEN].loadFromFile("assets/textures/spr_can_green.png");

	_collectPointsSoundBuffer.loadFromFile("assets/audio/snd_collect_points.ogg");
	_collectPointsSound.setBuffer(_collectPointsSoundBuffer);

	setSpawningPositions();
	createPaintBuckets();
}

PaintBucketsManager::~PaintBucketsManager()
{
	destroyPaintBuckets();
}

void PaintBucketsManager::createPaintBuckets()
{
	for (int i = 0; i < MAX_PAINT_BUCKETS; i++)
		_paintBuckets.push_back(new PaintBucket());
}

void PaintBucketsManager::destroyPaintBuckets()
{
	for (int i = 0; i < MAX_PAINT_BUCKETS; i++)
	{
		delete _paintBuckets[i];
		_paintBuckets[i] = nullptr;
	}
}

void PaintBucketsManager::setSpawningPositions()
{
	_spawningPositions[Utils::COLORS::RED].position = sf::Vector2f(450.f, -300.f);
	_spawningPositions[Utils::COLORS::RED].active = false;
	_spawningPositions[Utils::COLORS::RED].color = Utils::COLORS::RED;
	_spawningPositions[Utils::COLORS::GREEN].position = sf::Vector2f(580.f, -275.f);
	_spawningPositions[Utils::COLORS::GREEN].active = false;
	_spawningPositions[Utils::COLORS::GREEN].color = Utils::COLORS::GREEN;
	_spawningPositions[Utils::COLORS::BLUE].position = sf::Vector2f(700.f, -250.f);
	_spawningPositions[Utils::COLORS::BLUE].active = false;
	_spawningPositions[Utils::COLORS::BLUE].color = Utils::COLORS::BLUE;
}

void PaintBucketsManager::update(sf::Time deltaTime)
{
	spawnPaintBucket(deltaTime);

	for (int i = 0; i < MAX_PAINT_BUCKETS; i++)
	{
		if (_paintBuckets[i]->isActive())
		{
			_paintBuckets[i]->addAcceleration(sf::Vector2f(0.f, 9.8f));
			_paintBuckets[i]->update(deltaTime);
		}
	}	
}

void PaintBucketsManager::spawnPaintBucket(sf::Time deltaTime)
{
	_spawningTime += deltaTime;
	if (_spawningTime >= SPAWN_TIME)
	{
		for (int i = 0; i < MAX_PAINT_BUCKETS; i++)
		{
			if (!_paintBuckets[i]->isActive())
			{
				setRandomColorToPaintBucket(*_paintBuckets[i]);
				setRandomSpawningPositionToPaintBucket(*_paintBuckets[i]);
				setRandomVelocityToPaintBucket(*_paintBuckets[i]);
				_paintBuckets[i]->setActive(true);
				break;
			}
		}
		_spawningTime -= SPAWN_TIME;
	}
}

void PaintBucketsManager::setRandomSpawningPositionToPaintBucket(PaintBucket& paintBucket)
{
	Utils::COLORS randomIndex;
	do {
		randomIndex = static_cast<Utils::COLORS>(rand() % MAX_SPAWNING_POSITIONS);
	} while (_spawningPositions[randomIndex].active);
	sf::Vector2f randomPosition = _spawningPositions[randomIndex].position;
	_spawningPositions[randomIndex].active = true;
	paintBucket.setIndexOccupiedSpawningPosition(randomIndex);
	paintBucket.getSprite().setPosition(randomPosition);
}

void PaintBucketsManager::setRandomColorToPaintBucket(PaintBucket& paintBucket)
{
	int randomColor = rand() % Utils::COLORS::TOTAL;
	switch (randomColor)
	{
	case Utils::COLORS::BLUE:
		paintBucket.getSprite().setTexture(_paintBucketTextures[Utils::COLORS::BLUE]);
		paintBucket.setColor(Utils::COLORS::BLUE);
		break;
	case Utils::COLORS::RED:
		paintBucket.getSprite().setTexture(_paintBucketTextures[Utils::COLORS::RED]);
		paintBucket.setColor(Utils::COLORS::RED);
		break;
	case Utils::COLORS::GREEN:
		paintBucket.getSprite().setTexture(_paintBucketTextures[Utils::COLORS::GREEN]);
		paintBucket.setColor(Utils::COLORS::GREEN);
		break;
	default:
		break;
	}
}

void PaintBucketsManager::setRandomVelocityToPaintBucket(PaintBucket& paintBucket)
{
	float randomVelocity = static_cast<float>(rand() % 30 + 10);
	paintBucket.setVerticalVelocity(randomVelocity);
}

void PaintBucketsManager::checkIfPaintBucketLeftWindow(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_PAINT_BUCKETS; i++)
	{
		if (_paintBuckets[i]->isActive() && _paintBuckets[i]->getSprite().getPosition().y > window.getSize().y)
		{
			if (static_cast<int>(_paintBuckets[i]->getColor()) == _paintBuckets[i]->getIndexOccupiedSpawningPosition())
			{
				_game->updateScore();
				_collectPointsSound.play();
			}
			else
			{
				_game->decreaseLifeByOne();
			}
			_paintBuckets[i]->setActive(false);
			_spawningPositions[_paintBuckets[i]->getIndexOccupiedSpawningPosition()].active = false;
		}
	}
}

void PaintBucketsManager::reset()
{
	for (int i = 0; i < MAX_SPAWNING_POSITIONS; i++)
		_spawningPositions[i].active = false;

	for (int j = 0; j < MAX_PAINT_BUCKETS; j++)
	{
		setRandomColorToPaintBucket(*_paintBuckets[j]);
		setRandomSpawningPositionToPaintBucket(*_paintBuckets[j]);
		setRandomVelocityToPaintBucket(*_paintBuckets[j]);
		_paintBuckets[j]->setActive(true);
	}
}

void PaintBucketsManager::draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < MAX_PAINT_BUCKETS; i++)
		_paintBuckets[i]->draw(window);
}
