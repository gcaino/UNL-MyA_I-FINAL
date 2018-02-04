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
	void draw();

	void loadTexturesAndSetSprites();
	void drawLives() const;
	void pause();

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 480;
	const int FPS = 60;
	static const int MAX_LIVES = 5;

	sf::RenderWindow*	_window;
	int					_lives;
	int					_score;
	bool				_paused;

	sf::Texture			_backgroundTexture;
	sf::Sprite			_backgroundSprite;
	sf::Texture			_liveTexture;
	sf::Sprite			_liveSprite[MAX_LIVES];
	sf::Texture			_scoreBarTexture;
	sf::Sprite			_scoreBarSprite;
	sf::Texture			_gameOverTexture;
	sf::Sprite			_gameOverSprite;
};

#endif // !GAME_H

