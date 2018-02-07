#ifndef CANNON_H
#define CANNON_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include "enums.h"

class Ball;
class Game;

class Cannon
{
public:
	Cannon(Game* game);
	~Cannon();

	void processEvents(sf::Event event);
	void accumulatePower();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
	float getPower() { return _power; }
	void setPowerToBase() { _power = BASE_POWER; }
	std::vector<Ball*> getBalls() { return _balls; }
	void reset();

private:
	void lookAtMouse(sf::RenderWindow& window);
	void changeColorBall();
	void shootBall();
	void createColorBall();
	bool existInactiveBall();
	Ball* getInactiveColorBall();

	static const int MAX_COLORED_BALL = 3;
	const float BASE_POWER = 50.f;
	const float UNIT_INCREASE_POWER = 5.f;
	
	Utils::COLORS _currentColor;

	sf::Texture	_cannonTexture;
	sf::Sprite	_cannonSprite;
	sf::Texture	_cannonBlueBallTexture;
	sf::Texture	_cannonRedBallTexture;
	sf::Texture	_cannonGreenBallTexture;
	sf::Texture	_cannonColorBallTextures[MAX_COLORED_BALL];
	sf::Sprite	_cannonColorBallSprite;
	sf::Texture	_ballColorTextures[MAX_COLORED_BALL];

	sf::SoundBuffer _shootPaintSoundBuffer;
	sf::Sound		_shootPaintSound;
	sf::SoundBuffer	_changeColorSoundBuffer;
	sf::Sound		_changeColorSound;

	Game*			   _game;
	std::vector<Ball*> _balls;
	Ball*			   _currentColorBall;
	sf::Vector2f	   _currentVelocity;
	float			   _power;

};

#endif // CANNON_H

