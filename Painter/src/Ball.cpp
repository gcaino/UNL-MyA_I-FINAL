#include "Ball.h"

Ball::Ball()
	: _active(true)
	, _velocity(0.f, 0.f)
	, _acceleration(0.f, 0.f)
	, _position(0.f, 0.f)
{
}

Ball::~Ball()
{
}

void Ball::update(sf::Time deltaTime)
{
	movement(deltaTime);
}

void Ball::movement(sf::Time deltaTime)
{
	_position = _ballSprite.getPosition();

	_velocity.x += _acceleration.x * deltaTime.asSeconds();
	_velocity.y += _acceleration.y * deltaTime.asSeconds();

	_position.x += _velocity.x * deltaTime.asSeconds();
	_position.y += _velocity.y * deltaTime.asSeconds();

	_ballSprite.setPosition(_position);
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(_ballSprite);
}
