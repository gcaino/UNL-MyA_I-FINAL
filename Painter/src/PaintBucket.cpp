#include "PaintBucket.h"
// ----------------------------------------------------------------------------
PaintBucket::PaintBucket()
	: _active(false)
	, _velocity(0.f, 0.f)
	, _acceleration(0.f, 0.f)
{
}

PaintBucket::~PaintBucket()
{
}

void PaintBucket::update(sf::Time deltaTime)
{
	if (_active)
		verticalMovement(deltaTime);
}

// Para el movimiento de caida libre se implementan las ecucaciones analizadas en el video sobre 
// integradores númericos, puntualmente el tipo 'Symplectic Euler'.
// Dicho método permite resolver las formas del movimiento (velocidad, aceleración y posición)
// de manera numérica, general y aproximada.
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
