#include "PaintBucket.h"

PaintBucket::PaintBucket()
	: _active(false)
	, _velocity(0.f, 0.f)
	, _indexOccupiedSpawningPosition(0)
{
}

PaintBucket::~PaintBucket()
{
}

void PaintBucket::update(sf::Time deltaTime)
{
	if (_active)
	{
		verticalMovement(deltaTime);
	}
}

void PaintBucket::verticalMovement(sf::Time deltaTime)
{
		_sprite.move(_velocity.x, _velocity.y * deltaTime.asSeconds());
}

void PaintBucket::draw(sf::RenderWindow& window) const
{
	if (_active)
		window.draw(_sprite);
}
