#ifndef PAINT_BUCKET_H
#define PAINT_BUCKET_H

#include <SFML\Graphics.hpp>
#include "enums.h"

class PaintBucket
{
public:
	PaintBucket();
	~PaintBucket();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window) const;

	bool isActive() const { return _active; }
	void setActive(bool active) { _active = active; }
	sf::Sprite&	getSprite() { return _sprite; }
	void setVerticalVelocity(float yVelocity) { _velocity.y = yVelocity; }
	void setIndexOccupiedSpawningPosition(Utils::COLORS index) { _indexOccupiedSpawningPosition = index; }
	Utils::COLORS getIndexOccupiedSpawningPosition() const { return _indexOccupiedSpawningPosition; }

	void setAcceleration(sf::Vector2f acceleration) { _acceleration = acceleration; }
	void addAcceleration(sf::Vector2f acceleration) { 
		_acceleration.x += acceleration.x;
		_acceleration.y += acceleration.y;
	}

	Utils::COLORS getColor() const { return _color; }
	void setColor(Utils::COLORS color) { _color = color; }

private:
	void verticalMovement(sf::Time deltaTime);

	sf::Sprite		_sprite;
	bool			_active;
	sf::Vector2f	_velocity;
	sf::Vector2f	_acceleration;
	Utils::COLORS	_indexOccupiedSpawningPosition;
	Utils::COLORS	_color;

};

#endif // PAINT_BUCKET_H
