#ifndef CANNON_H
#define CANNON_H

#include <SFML\Graphics.hpp>
#include <vector>

class Ball;

class Cannon
{
public:
	Cannon();
	~Cannon();

	void changeColorBall();
	void shootBall();
	void accumulatePower();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
	float getPower() { return _power; }

private:
	void lookAtMouse(sf::RenderWindow& window);
	void createColorBall();
	bool existInactiveBall();
	Ball* getInactiveColorBall();

	static const int MAX_COLORED_BALL = 3;
	const float BASE_POWER = 50.f;
	const float UNIT_INCREASE_POWER = 5.f;
	enum COLORS { RED, BLUE, GREEN };
	int			_currentColor;

	sf::Texture	_cannonTexture;
	sf::Sprite	_cannonSprite;

	sf::Texture	_cannonBlueBallTexture;
	sf::Texture	_cannonRedBallTexture;
	sf::Texture	_cannonGreenBallTexture;

	sf::Texture	_cannonColorBallTextures[MAX_COLORED_BALL];
	sf::Sprite	_cannonColorBallSprite;

	sf::Texture	_ballColorTextures[MAX_COLORED_BALL];

	std::vector<Ball*> _balls;
	Ball*			   _currentColorBall;
	sf::Vector2f	   _currentVelocity;

	float			   _power;

};

#endif // CANNON_H

