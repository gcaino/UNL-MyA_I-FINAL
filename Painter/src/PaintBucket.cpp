#include "PaintBucket.h"

PaintBucket::PaintBucket()
	: _active(false)
	, _velocity(0.f, 0.f)
	, _acceleration(0.f, 0.f)
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
	_velocity.x += _acceleration.x * deltaTime.asSeconds();
	_velocity.y += _acceleration.y * deltaTime.asSeconds();

	_sprite.move(_velocity.x * deltaTime.asSeconds(), 
				 _velocity.y * deltaTime.asSeconds());

	_acceleration.x = 0.f;
	_acceleration.y = 0.f;
}

void PaintBucket::draw(sf::RenderWindow& window) const
{
	if (_active)
		window.draw(_sprite);
}
