#include "Ball.h"

Ball::Ball()
	: _active(true)
	, _velocity(0.f, 0.f)
	, _acceleration(0.f, 0.f)
{
}

Ball::~Ball()
{
}

void Ball::update(sf::Time deltaTime)
{
	obliqueMovement(deltaTime);
}

void Ball::obliqueMovement(sf::Time deltaTime)
{
	_velocity.x += _acceleration.x * deltaTime.asSeconds();
	_velocity.y += _acceleration.y * deltaTime.asSeconds();

	_ballSprite.move(_velocity.x * deltaTime.asSeconds(),
					 _velocity.y * deltaTime.asSeconds());
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(_ballSprite);
}
