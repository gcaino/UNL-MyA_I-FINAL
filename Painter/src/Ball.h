#ifndef BALL_H
#define BALL_H

#include <SFML\Graphics.hpp>

class Ball
{
public:
	Ball();
	~Ball();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

	bool isActive() const { return _active; }
	void setActive(bool active) { _active = active; }
	void setSpriteColor(sf::Texture& texture) { _ballSprite.setTexture(texture); }
	void setPosition(sf::Vector2f position) { _ballSprite.setPosition(position); }
	void setAcceleration(sf::Vector2f acceleration) { _acceleration = acceleration; }
	void setVelocity(sf::Vector2f velocity) { _velocity = velocity; }
	void setRotation(float rotation) { _ballSprite.setRotation(rotation); }
	void setOrigin(sf::Vector2f origin) { _ballSprite.setOrigin(origin); }
	sf::Sprite& getSprite() { return _ballSprite; }

private:
	void obliqueMovement(sf::Time deltaTime);

	sf::Sprite		_ballSprite;
	bool			_active;
	sf::Vector2f	_velocity;
	sf::Vector2f	_acceleration;

};

#endif // BALL_H

