#ifndef PAINT_BUCKETS_MANAGER_H
#define PAINT_BUCKETS_MANAGER_H
// ----------------------------------------------------------------------------
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include "PaintBucket.h"
#include "enums.h"
// ----------------------------------------------------------------------------
class Game;
/**
* La clase PaintBucketsManager es la encargada de gestionar la totalidad de los 
* baldes de pintura. Para tal objetivo se utilizó una estructura de datos del tipo
* array dinámico.
* Entre sus métodos principales se encuentran los encargados de 'spawnear' baldes,
* setearles valores random en sus distintos atributos, controlar el estado, 
* así como también ir gestionando el incremento de la dificultad (mayor velocidad).
*/
// ----------------------------------------------------------------------------
class PaintBucketsManager
{
public:
	PaintBucketsManager(Game* game, int totalPaintBuckets);
	~PaintBucketsManager();

	void update(sf::Time deltaTime);
	void checkIfPaintBucketLeftWindow(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) const;
	std::vector<PaintBucket*> getPaintBuckets() { return _paintBuckets; }
	sf::Texture& getPaintBucketTexturesByColor(Utils::COLORS color) { return _paintBucketTextures[color]; }
	void reset();

private:
	void createPaintBuckets(int quantity);
	void destroyPaintBuckets();
	void spawnPaintBucket(sf::Time deltaTime);
	void setSpawningPositions();
	void setRandomColorToPaintBucket(PaintBucket& paintBucket);
	void setRandomSpawningPositionToPaintBucket(PaintBucket& paintBucket);
	void setRandomVelocityToPaintBucket(PaintBucket& paintBucket);
	void increaseVelocityRange(sf::Time deltaTime);
	
	static const int MAX_PAINT_BUCKETS_TEXTURES = 3;
	static const int MAX_SPAWNING_POSITIONS = 3;
	const sf::Time SPAWN_TIME = sf::seconds(3.f);
	const sf::Time CHANGE_VELOCITY_TIME = sf::seconds(10.f);
	const int BASE_MIN_AMOUNT_PAINT_BUCKETS = 3;
	const int BASE_MIN_VELOCITY = 10;
	const int BASE_MAX_VELOCITY = 30;

	Game*						_game;
	std::vector<PaintBucket*>	_paintBuckets; // Contenedor de punteros de Baldes de Pintura
	sf::Time					_spawningTime;
	sf::Texture					_paintBucketTextures[MAX_PAINT_BUCKETS_TEXTURES];
	int							_maxVelocity;
	int							_minVelocity;
	sf::Time					_elapsedTimeChangeVelocity;

	struct SpawningPosition
	{
		sf::Vector2f position;
		Utils::COLORS color;
		bool active;
	};

	SpawningPosition _spawningPositions[MAX_SPAWNING_POSITIONS];

	sf::SoundBuffer _collectPointsSoundBuffer;
	sf::Sound		_collectPointsSound;
};
// ----------------------------------------------------------------------------
#endif // PAINT_BUCKETS_MANAGER_H

