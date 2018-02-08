#include <iostream>
#include "PaintBucketsManager.h"
#include "Game.h"
#include "PaintBucket.h"
#include "enums.h"
// ----------------------------------------------------------------------------
PaintBucketsManager::PaintBucketsManager(Game* game, int totalPaintBuckets)
	: _game(game)
	, _spawningTime(sf::seconds(0.f))
	, _minVelocity(BASE_MIN_VELOCITY)
	, _maxVelocity(BASE_MAX_VELOCITY)
	, _elapsedTimeChangeVelocity(sf::seconds(0.f))
{
	_paintBucketTextures[Utils::COLORS::BLUE].loadFromFile("assets/textures/spr_can_blue.png");
	_paintBucketTextures[Utils::COLORS::RED].loadFromFile("assets/textures/spr_can_red.png");
	_paintBucketTextures[Utils::COLORS::GREEN].loadFromFile("assets/textures/spr_can_green.png");

	_collectPointsSoundBuffer.loadFromFile("assets/audio/snd_collect_points.ogg");
	_collectPointsSound.setBuffer(_collectPointsSoundBuffer);

	setSpawningPositions();
	createPaintBuckets(totalPaintBuckets);
}

PaintBucketsManager::~PaintBucketsManager()
{
	destroyPaintBuckets();
}

void PaintBucketsManager::createPaintBuckets(int quantity)
{
	for (int i = 0; i < quantity; i++)
		_paintBuckets.push_back(new PaintBucket());
}

void PaintBucketsManager::destroyPaintBuckets()
{
	for (size_t i = 0; i < _paintBuckets.size(); i++)
		delete _paintBuckets[i];
}

void PaintBucketsManager::setSpawningPositions()
{
	_spawningPositions[Utils::COLORS::RED].position = sf::Vector2f(585.f, -300.f);
	_spawningPositions[Utils::COLORS::RED].active = false;
	_spawningPositions[Utils::COLORS::RED].color = Utils::COLORS::RED;
	_spawningPositions[Utils::COLORS::GREEN].position = sf::Vector2f(754.f, -275.f);
	_spawningPositions[Utils::COLORS::GREEN].active = false;
	_spawningPositions[Utils::COLORS::GREEN].color = Utils::COLORS::GREEN;
	_spawningPositions[Utils::COLORS::BLUE].position = sf::Vector2f(908.f, -250.f);
	_spawningPositions[Utils::COLORS::BLUE].active = false;
	_spawningPositions[Utils::COLORS::BLUE].color = Utils::COLORS::BLUE;
}

void PaintBucketsManager::update(sf::Time deltaTime)
{
	spawnPaintBucket(deltaTime);
	increaseVelocityRange(deltaTime);
	
	for (size_t i = 0; i < _paintBuckets.size(); i++)
	{
		if (_paintBuckets[i]->isActive())
		{
			_paintBuckets[i]->addAcceleration(sf::Vector2f(0.f, 9.8f));
			_paintBuckets[i]->update(deltaTime);
		}
	}	
}

// Pasado el timepo de spawneo se itera sobre el contenedor de baldes 
// en busca de instancias inactivas. De encontrarse una se setean nuevamente
// sus valores y se decrementa el contador de tiempo.
void PaintBucketsManager::spawnPaintBucket(sf::Time deltaTime)
{
	_spawningTime += deltaTime;
	if (_spawningTime >= SPAWN_TIME)
	{
		for (size_t i = 0; i < _paintBuckets.size(); i++)
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

// Dicho método itera hasta encontrar una posición de spawneo no activa, para luego
// setear dicha posición disponible al próximo balde de pintura.
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

// Se asigna una velocidad random, definida en un rango que va variando a lo largo del tiempo
// de juego.
void PaintBucketsManager::setRandomVelocityToPaintBucket(PaintBucket& paintBucket)
{
	float randomVelocity = static_cast<float>(rand() % _maxVelocity + _minVelocity);
	paintBucket.setVerticalVelocity(randomVelocity);
}

// Cheque si el balde de pintura, al salir de la pantalla, contiene el mismo color de la 
// la posición en donde fue spawneado. De ser así se suma puntaje, en caso contrario 
// se pierde una vida. 
// Finalmente, se ponen a disponibilidad tanto el balde como la posición de spawneo, permitiendo
// reutilizar recursos ya instanciados en memoria, para el caso de los baldes de pintura.
void PaintBucketsManager::checkIfPaintBucketLeftWindow(sf::RenderWindow& window)
{
	for (size_t i = 0; i < _paintBuckets.size(); i++)
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

// Permite ir incrementando la dificultad del jueo a medida que se avanza en
// el tiempo, a partir del incremento del rango de velocidad.
void PaintBucketsManager::increaseVelocityRange(sf::Time deltaTime)
{
	_elapsedTimeChangeVelocity += deltaTime;
	if (_elapsedTimeChangeVelocity >= CHANGE_VELOCITY_TIME)
	{
		_minVelocity += 10;
		_maxVelocity += 10;
		_elapsedTimeChangeVelocity -= CHANGE_VELOCITY_TIME;
	}
}

void PaintBucketsManager::reset()
{
	for (int i = 0; i < MAX_SPAWNING_POSITIONS; i++)
		_spawningPositions[i].active = false;

	_paintBuckets.clear();
	createPaintBuckets(BASE_MIN_AMOUNT_PAINT_BUCKETS);

	_minVelocity = BASE_MIN_VELOCITY;
	_maxVelocity = BASE_MAX_VELOCITY;
}

void PaintBucketsManager::draw(sf::RenderWindow& window) const
{
	for (size_t i = 0; i < _paintBuckets.size(); i++)
		_paintBuckets[i]->draw(window);
}
