#include "Cannon.h"

Cannon::Cannon()
{
	_cannonTexture.loadFromFile("assets/textures/spr_cannon_barrel.png");
	_cannonSprite.setTexture(_cannonTexture);
	_cannonSprite.setOrigin(33.f, 33.f);
	_cannonSprite.setPosition(73.f, 410.f);

	_cannonColoredBallTextures[COLORS::RED].loadFromFile("assets/textures/spr_cannon_red.png");
	_cannonColoredBallTextures[COLORS::BLUE].loadFromFile("assets/textures/spr_cannon_blue.png");
	_cannonColoredBallTextures[COLORS::GREEN].loadFromFile("assets/textures/spr_cannon_green.png");

	_currentColor = COLORS::RED;

	_cannonColoredBallSprite.setTexture(_cannonColoredBallTextures[_currentColor]);
	_cannonColoredBallSprite.setPosition(_cannonSprite.getPosition().x - 17.f,
										 _cannonSprite.getPosition().y - 15.f);
}

Cannon::~Cannon()
{
}

void Cannon::processEvents()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		shootBall();
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		changeColoredBall();
	}
}

void Cannon::shootBall()
{

}

void Cannon::changeColoredBall()
{
	++_currentColor;
	if (_currentColor >= MAX_COLORED_BALL)
		_currentColor = COLORS::RED;
	_cannonColoredBallSprite.setTexture(_cannonColoredBallTextures[_currentColor]);
}

void Cannon::update(sf::Time deltaTime)
{
	
}

void Cannon::lookAtMouse(sf::RenderWindow& window)
{
	const float PI = 3.14159265;

	sf::Vector2i mouseCurrentPosition = sf::Mouse::getPosition(window);
	sf::Vector2f spriteCurrentPosition = _cannonSprite.getPosition();

	float deltaX = mouseCurrentPosition.x - spriteCurrentPosition.x;
	float deltaY = mouseCurrentPosition.y - spriteCurrentPosition.y;

	float rotation = (atan2(deltaY, deltaX)) * 180 / PI;

	_cannonSprite.setRotation(rotation);
}

void Cannon::draw(sf::RenderWindow& window)
{
	lookAtMouse(window);
	window.draw(_cannonSprite);
	window.draw(_cannonColoredBallSprite);
}
