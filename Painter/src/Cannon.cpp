#include "Cannon.h"

Cannon::Cannon()
{
	_texture.loadFromFile("assets/textures/spr_cannon_barrel.png");
	_sprite.setTexture(_texture);
	_sprite.setOrigin(33.f, 33.f);
	_sprite.setPosition(73.f, 410.f);
}

Cannon::~Cannon()
{
}

void Cannon::processEvents()
{
	if (sf::Mouse::Left)
	{
		shootBall();
	}
	else if (sf::Mouse::Right)
	{
		changeColoredBall();
	}
}

void Cannon::shootBall()
{

}

void Cannon::changeColoredBall()
{

}

void Cannon::update(sf::Time deltaTime)
{
	
}

void Cannon::lookAtMouse(sf::RenderWindow& window)
{
	const float PI = 3.14159265;

	sf::Vector2i mouseCurrentPosition = sf::Mouse::getPosition(window);
	sf::Vector2f spriteCurrentPosition = _sprite.getPosition();

	float deltaX = mouseCurrentPosition.x - spriteCurrentPosition.x;
	float deltaY = mouseCurrentPosition.y - spriteCurrentPosition.y;

	float rotation = (atan2(deltaY, deltaX)) * 180 / PI;

	_sprite.setRotation(rotation);
}

void Cannon::draw(sf::RenderWindow& window)
{
	lookAtMouse(window);
	window.draw(_sprite);
}
