#ifndef PAINT_BUCKET_H
#define PAINT_BUCKET_H

#include <SFML\Graphics.hpp>

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
	void setIndexOccupiedSpawningPosition(int index) { _indexOccupiedSpawningPosition = index; }
	int getIndexOccupiedSpawningPosition() const { return _indexOccupiedSpawningPosition; }

private:
	void verticalMovement(sf::Time deltaTime);

	sf::Sprite		_sprite;
	bool			_active;
	sf::Vector2f	_velocity;
	int				_indexOccupiedSpawningPosition;
};

#endif // PAINT_BUCKET_H
