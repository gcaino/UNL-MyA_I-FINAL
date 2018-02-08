#ifndef BALL_H
#define BALL_H
// ----------------------------------------------------------------------------
#include <SFML\Graphics.hpp>
#include "enums.h"
// ----------------------------------------------------------------------------
/**
* La clase Ball representa a cada una de las pelotas de pintura que el jugador
* puede lanzar desde el ca�on. 
* Lo m�s destacado es el movimiento, para lo cual se implementaron en el 
* m�todo 'movement' las ecucaciones vistas tanto en la teor�a como en los videos 
* anexos sobre integradores num�ricos.
*/
// ----------------------------------------------------------------------------
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
	
	Utils::COLORS getColor() const { return _color; }
	void setColor(Utils::COLORS color) { _color = color; }

private:
	void movement(sf::Time deltaTime); // Implementa Integrador Num�rico para movimientos f�sicos con aceleraci�n

	sf::Sprite		_ballSprite;
	bool			_active;
	sf::Vector2f	_velocity;
	sf::Vector2f	_acceleration;
	sf::Vector2f	_position;
	Utils::COLORS	_color;

};
// ----------------------------------------------------------------------------
#endif // BALL_H

