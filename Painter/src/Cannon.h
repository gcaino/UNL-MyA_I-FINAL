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
	void accumulateVelocityXAxis();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

private:
	void lookAtMouse(sf::RenderWindow& window);
	void updateShootPosition();
	void createColorBall();
	bool existInactiveBall();
	Ball* getInactiveColorBall();

	static const int MAX_COLORED_BALL = 3;
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

};

#endif // CANNON_H

