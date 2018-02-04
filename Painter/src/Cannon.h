#ifndef CANNON_H
#define CANNON_H

#include <SFML\Graphics.hpp>

class Cannon
{
public:
	Cannon();
	~Cannon();

	void processEvents();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

private:
	void lookAtMouse(sf::RenderWindow& window);
	void shootBall();
	void changeColoredBall();

	static const int MAX_COLORED_BALL = 3;
	enum COLORS { RED, BLUE, GREEN };
	int			_currentColor;

	sf::Texture	_cannonTexture;
	sf::Sprite	_cannonSprite;

	sf::Texture	_cannonBlueBallTexture;
	sf::Texture	_cannonRedBallTexture;
	sf::Texture	_cannonGreenBallTexture;

	sf::Texture	_cannonColoredBallTextures[MAX_COLORED_BALL];
	sf::Sprite	_cannonColoredBallSprite;

};

#endif // CANNON_H

