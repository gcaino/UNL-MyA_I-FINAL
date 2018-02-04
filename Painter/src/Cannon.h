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

	sf::Texture	_texture;
	sf::Sprite	_sprite;

};

#endif // CANNON_H

