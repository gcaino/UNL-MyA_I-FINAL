#ifndef PAINT_BUCKETS_MANAGER_H
#define PAINT_BUCKETS_MANAGER_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include "PaintBucket.h"
#include "enums.h"

class Game;

class PaintBucketsManager
{
public:
	PaintBucketsManager(Game* game);
	~PaintBucketsManager();

	void update(sf::Time deltaTime);
	void checkIfPaintBucketLeftWindow(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) const;
	std::vector<PaintBucket*> getPaintBuckets() { return _paintBuckets; }
	sf::Texture& getPaintBucketTexturesByColor(Utils::COLORS color) { return _paintBucketTextures[color]; }
	void reset();

private:
	void createPaintBuckets();
	void destroyPaintBuckets();
	void spawnPaintBucket(sf::Time deltaTime);
	void setSpawningPositions();
	void setRandomColorToPaintBucket(PaintBucket& paintBucket);
	void setRandomSpawningPositionToPaintBucket(PaintBucket& paintBucket);
	void setRandomVelocityToPaintBucket(PaintBucket& paintBucket);
	void incremetMaxVelocity(sf::Time deltaTime);
	
	static const int MAX_PAINT_BUCKETS = 3;
	static const int MAX_SPAWNING_POSITIONS = 3;
	const sf::Time SPAWN_TIME = sf::seconds(3.f);
	const sf::Time CHANGE_VELOCITY_TIME = sf::seconds(10.f);
	const int BASE_VELOCITY = 30;

	Game*		 _game;
	std::vector<PaintBucket*> _paintBuckets;
	sf::Time     _spawningTime;
	sf::Texture  _paintBucketTextures[MAX_PAINT_BUCKETS];
	int			 _maxVelocity;
	sf::Time	 _elapsedTimeChangeVelocity;

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

#endif // PAINT_BUCKETS_MANAGER_H

