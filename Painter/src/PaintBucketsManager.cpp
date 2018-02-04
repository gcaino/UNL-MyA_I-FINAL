#include <iostream>
#include "PaintBucketsManager.h"
#include "PaintBucket.h"

PaintBucketsManager::PaintBucketsManager()
{
	_paintBucketBlueTexture.loadFromFile("assets/textures/spr_can_blue.png");
	_paintBucketRedTexture.loadFromFile("assets/textures/spr_can_red.png");
	_paintBucketGreenTexture.loadFromFile("assets/textures/spr_can_green.png");

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
		_paintBuckets[i] = new PaintBucket();
}

void PaintBucketsManager::destroyPaintBuckets()
{
	for (int i = 0; i < MAX_PAINT_BUCKETS; i++)
		delete _paintBuckets[i];
}

void PaintBucketsManager::setSpawningPositions()
{
	_spawningPositions[0].position = sf::Vector2f(450.f, -150.f);
	_spawningPositions[0].active = false;
	_spawningPositions[1].position = sf::Vector2f(580.f, -150.f);
	_spawningPositions[1].active = false;
	_spawningPositions[2].position = sf::Vector2f(700.f, -150.f);
	_spawningPositions[2].active = false;
}

void PaintBucketsManager::update(sf::Time deltaTime)
{
	spawnPaintBucket();

	for (int i = 0; i < MAX_PAINT_BUCKETS; i++)
	{
		_paintBuckets[i]->addAcceleration(sf::Vector2f(0.f, 9.8f));
		_paintBuckets[i]->update(deltaTime);
	}
		
}

void PaintBucketsManager::spawnPaintBucket()
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
}

void PaintBucketsManager::setRandomSpawningPositionToPaintBucket(PaintBucket& paintBucket)
{
	int randomIndex;
	do {
		randomIndex = rand() % MAX_SPAWNING_POSITIONS;
	} while (_spawningPositions[randomIndex].active);
	sf::Vector2f randomPosition = _spawningPositions[randomIndex].position;
	_spawningPositions[randomIndex].active = true;
	paintBucket.setIndexOccupiedSpawningPosition(randomIndex);
	paintBucket.getSprite().setPosition(randomPosition);
}

void PaintBucketsManager::setRandomColorToPaintBucket(PaintBucket& paintBucket)
{
	int randomColor = rand() % COLORS::MAX;
	switch (randomColor)
	{
	case COLORS::BLUE:
		paintBucket.getSprite().setTexture(_paintBucketBlueTexture);
		break;
	case COLORS::RED:
		paintBucket.getSprite().setTexture(_paintBucketRedTexture);
		break;
	case COLORS::GREEN:
		paintBucket.getSprite().setTexture(_paintBucketGreenTexture);
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
		if (_paintBuckets[i]->getSprite().getPosition().y > window.getSize().y)
		{
			_paintBuckets[i]->setActive(false);
			_spawningPositions[_paintBuckets[i]->getIndexOccupiedSpawningPosition()].active = false;
		}
	}
}

void PaintBucketsManager::draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < MAX_PAINT_BUCKETS; i++)
		_paintBuckets[i]->draw(window);
}
