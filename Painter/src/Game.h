#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void loop();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int FPS = 60;
	const int MAX_LIFES = 5;

	sf::RenderWindow*	_window;
	int					_lifes;
	int					_score;
};

#endif // !GAME_H

