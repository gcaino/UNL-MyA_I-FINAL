#include "Cannon.h"
#include "Ball.h"

Cannon::Cannon()
	: _currentVelocity(0.f, 0.f)
	, _power(BASE_POWER)
{
	_cannonTexture.loadFromFile("assets/textures/spr_cannon_barrel.png");
	_cannonSprite.setTexture(_cannonTexture);
	_cannonSprite.setOrigin(34.f, 34.f);
	_cannonSprite.setPosition(72.f, 405.f);

	_cannonColorBallTextures[COLORS::RED].loadFromFile("assets/textures/spr_cannon_red.png");
	_cannonColorBallTextures[COLORS::BLUE].loadFromFile("assets/textures/spr_cannon_blue.png");
	_cannonColorBallTextures[COLORS::GREEN].loadFromFile("assets/textures/spr_cannon_green.png");

	_ballColorTextures[COLORS::RED].loadFromFile("assets/textures/spr_ball_red.png");
	_ballColorTextures[COLORS::BLUE].loadFromFile("assets/textures/spr_ball_blue.png");
	_ballColorTextures[COLORS::GREEN].loadFromFile("assets/textures/spr_ball_green.png");

	_currentColor = COLORS::RED;

	_cannonColorBallSprite.setTexture(_cannonColorBallTextures[_currentColor]);
	_cannonColorBallSprite.setPosition(_cannonSprite.getPosition().x - 17.f,
									   _cannonSprite.getPosition().y - 15.f);
}

Cannon::~Cannon()
{
}

void Cannon::shootBall()
{
	if (existInactiveBall())
	{
		_currentColorBall = getInactiveColorBall();
	}
	else
	{
		createColorBall();
		_currentColorBall = _balls.back();
	}

	_currentColorBall->setSpriteColor(_cannonColorBallTextures[_currentColor]);
	_currentColorBall->setOrigin(sf::Vector2f(_currentColorBall->getSprite().getGlobalBounds().width / 2,
											  _currentColorBall->getSprite().getGlobalBounds().height / 2));
	_currentColorBall->getSprite().setScale(0.75f, 0.75f);
	_currentColorBall->getSprite().setPosition(72.f + 110.f, 405.f);

	sf::Transform tmpTransform;
	tmpTransform.rotate(_cannonSprite.getRotation(), _cannonSprite.getPosition());
	sf::Vector2f point = tmpTransform.transformPoint(_currentColorBall->getSprite().getPosition());
	_currentColorBall->setPosition(point);

	_currentColorBall->setAcceleration(sf::Vector2f(0.f, 25.f));

	const float PI = 3.14159265f;
	_currentVelocity.x = _power * cos(_cannonSprite.getRotation() * PI / 180);
	_currentVelocity.y = _power * sin(_cannonSprite.getRotation() * PI / 180);
	_currentColorBall->setVelocity(_currentVelocity);

	_power = BASE_POWER;
}

void Cannon::accumulatePower()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		_power += UNIT_INCREASE_POWER;
}

bool Cannon::existInactiveBall()
{
	if (!_balls.empty())
	{
		for (size_t i = 0; i < _balls.size(); i++)
		{
			if (!_balls[i]->isActive())
				return true;
		}
	}
	return false;
}

Ball* Cannon::getInactiveColorBall()
{
	if (!_balls.empty())
	{
		for (size_t i = 0; i < _balls.size(); i++)
		{
			if (!_balls[i]->isActive())
			{
				_balls[i]->setActive(true);
				return _balls[i];
			}
		}
	}
	return nullptr;
}

void Cannon::createColorBall()
{
	_balls.push_back(new Ball());
}

void Cannon::changeColorBall()
{
	++_currentColor;
	if (_currentColor >= MAX_COLORED_BALL)
		_currentColor = COLORS::RED;
	_cannonColorBallSprite.setTexture(_cannonColorBallTextures[_currentColor]);
}

void Cannon::update(sf::Time deltaTime)
{
	for (size_t i = 0; i < _balls.size(); i++)
	{
		if (_balls[i]->isActive())
			_balls[i]->update(deltaTime);
	}
}

void Cannon::lookAtMouse(sf::RenderWindow& window)
{
	const float PI = 3.14159265f;

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

	for (size_t i = 0; i < _balls.size(); i++)
	{
		if (_balls[i]->isActive())
			_balls[i]->draw(window);
	}

	window.draw(_cannonSprite);
	window.draw(_cannonColorBallSprite);

	
}