#ifndef PAINT_BUCKETS_MANAGER_H
#define PAINT_BUCKETS_MANAGER_H

#include <SFML\Graphics.hpp>
#include "PaintBucket.h"

class PaintBucketsManager
{
public:
	PaintBucketsManager();
	~PaintBucketsManager();

	void update(sf::Time deltaTime);
	void checkIfPaintBucketLeftWindow(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) const;

private:
	void createPaintBuckets();
	void destroyPaintBuckets();
	void spawnPaintBucket();
	void setSpawningPositions();
	void setRandomColorToPaintBucket(PaintBucket& paintBucket);
	void setRandomSpawningPositionToPaintBucket(PaintBucket& paintBucket);
	void setRandomVelocityToPaintBucket(PaintBucket& paintBucket);

	static const int MAX_PAINT_BUCKETS = 3;
	static const int MAX_SPAWNING_POSITIONS = 3;

	enum COLORS { BLUE, RED, GREEN, MAX };

	sf::Texture	_paintBucketBlueTexture;
	sf::Texture	_paintBucketRedTexture;
	sf::Texture	_paintBucketGreenTexture;

	PaintBucket* _paintBuckets[MAX_PAINT_BUCKETS];

	struct SpawningPosition
	{
		sf::Vector2f position;
		bool active;
	};

	SpawningPosition _spawningPositions[MAX_SPAWNING_POSITIONS];
};

#endif // PAINT_BUCKETS_MANAGER_H

