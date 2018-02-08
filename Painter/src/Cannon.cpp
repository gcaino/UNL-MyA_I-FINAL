#include "Cannon.h"
#include "Ball.h"
#include "Game.h"
#include "enums.h"
// ----------------------------------------------------------------------------
Cannon::Cannon(Game* game)
	: _game(game)
	, _currentVelocity(0.f, 0.f)
	, _power(BASE_POWER)
	, _origin(43.f, 43.f)
	, _position(92.f, 648.f)
{
	_cannonTexture.loadFromFile("assets/textures/spr_cannon_barrel_1024.png");
	_cannonSprite.setTexture(_cannonTexture);
	_cannonSprite.setOrigin(_origin.x, _origin.y);
	_cannonSprite.setPosition(_position.x, _position.y);

	_cannonColorBallTextures[Utils::COLORS::RED].loadFromFile("assets/textures/spr_cannon_red_1024.png");
	_cannonColorBallTextures[Utils::COLORS::BLUE].loadFromFile("assets/textures/spr_cannon_blue_1024.png");
	_cannonColorBallTextures[Utils::COLORS::GREEN].loadFromFile("assets/textures/spr_cannon_green_1024.png");

	_ballColorTextures[Utils::COLORS::RED].loadFromFile("assets/textures/spr_ball_red.png");
	_ballColorTextures[Utils::COLORS::BLUE].loadFromFile("assets/textures/spr_ball_blue.png");
	_ballColorTextures[Utils::COLORS::GREEN].loadFromFile("assets/textures/spr_ball_green.png");

	_currentColor = Utils::COLORS::RED;

	_cannonColorBallSprite.setTexture(_cannonColorBallTextures[_currentColor]);
	_cannonColorBallSprite.setPosition(_cannonSprite.getPosition().x - 21.f,
									   _cannonSprite.getPosition().y - 20.f);

	_shootPaintSoundBuffer.loadFromFile("assets/audio/snd_shoot_paint.ogg");
	_shootPaintSound.setBuffer(_shootPaintSoundBuffer);

	_changeColorSoundBuffer.loadFromFile("assets/audio/snd_switch.ogg");
	_changeColorSound.setBuffer(_changeColorSoundBuffer);
}

Cannon::~Cannon()
{
}

void Cannon::processEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Right)
	{
		changeColorBall();
	}
	else if (event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		shootBall();
	}
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
	_currentColorBall->setColor(_currentColor);
	_currentColorBall->setOrigin(sf::Vector2f(_currentColorBall->getSprite().getGlobalBounds().width / 2,
											  _currentColorBall->getSprite().getGlobalBounds().height / 2));
	_currentColorBall->getSprite().setScale(0.75f, 0.75f);
	_currentColorBall->getSprite().setPosition(_position.x + 140.f, _position.y);

	// Se instancia un tipo 'Transform' al cual se le aplica la rotación del cañon, junto con su posición,
	// y luego se aplica dicha rotación al sprite de la pelota. De dicha manera se logra que las pelotas
	// sean lanzadas por el cañon correctamente.
	sf::Transform tmpTransform;
	tmpTransform.rotate(_cannonSprite.getRotation(), _cannonSprite.getPosition());
	sf::Vector2f point = tmpTransform.transformPoint(_currentColorBall->getSprite().getPosition());
	_currentColorBall->setPosition(point);

	_currentColorBall->setAcceleration(sf::Vector2f(0.f, 225.f));

	const float PI = 3.14159265f;
	// Para obtener un tiro oblicuo, aplicando lo visto en la teoría sobre cinemática, 
	// se descompone la velocidad en sus componentes vectoriales, en el eje x y en el eje y.
	// Para conocer el valor de la misma en cada eje, se recurre a las funciones trigonométricas
	// aplicadas al ángulo de rotación del cañon.
	_currentVelocity.x = _power * cos(_cannonSprite.getRotation() * PI / 180);
	_currentVelocity.y = _power * sin(_cannonSprite.getRotation() * PI / 180);
	_currentColorBall->setVelocity(_currentVelocity);

	_power = BASE_POWER;

	_shootPaintSound.play();
}

// Mientras el jugador mantiene presiona el botón izquierdo del mouse
// se incrementa en 'x' unidades el poder de lanzamiento.
void Cannon::accumulatePower()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_power += UNIT_INCREASE_POWER;
	}
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

// En dicho método se utiliza una sobrecarga del operador de postincremento
// del tipo definido 'COLORS', contenido en el espacio de nombre 'Utils'.
// Ver archivo 'enums.h'
void Cannon::changeColorBall()
{
	++_currentColor;
	if (_currentColor >= Utils::COLORS::TOTAL)
		_currentColor = Utils::COLORS::RED;
	_cannonColorBallSprite.setTexture(_cannonColorBallTextures[_currentColor]);

	_changeColorSound.play();
}

void Cannon::update(sf::Time deltaTime)
{
	lookAtMouse(*_game->getWindow());

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

	// La función atan2 retorna sus valores expresados en radianes, por tal motivo
	// como el método 'setRotation' de SFML recibe grados se debe realizar la
	// conversión del Sistema Circular (radianes) al Sistema Sexagesimal (grados)
	float rotation = (atan2(deltaY, deltaX)) * 180 / PI;

	_cannonSprite.setRotation(rotation);
}

void Cannon::reset()
{
	for (size_t i = 0; i < _balls.size(); i++)
		_balls[i]->setActive(false);
}

void Cannon::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < _balls.size(); i++)
	{
		if (_balls[i]->isActive())
			_balls[i]->draw(window);
	}

	window.draw(_cannonSprite);
	window.draw(_cannonColorBallSprite);

	
}
