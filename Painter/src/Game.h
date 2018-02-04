#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>

class Cannon;
class PaintBucketsManager;

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

	void addSpriteToMousePointer();
	void loadTexturesAndSetSprites();
	void loadFontsAndSetTexts();
	void drawLives() const;
	void pause();
	void setScore();

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 480;
	const int FPS = 60;
	static const int MAX_LIVES = 5;

	sf::RenderWindow*	 _window;
	Cannon*				 _cannon;
	PaintBucketsManager* _paintBucketsManager;
	int					 _lives;
	int					 _score;
	bool				 _paused;

	sf::Texture			_crosshairTexture;
	sf::Sprite			_crosshairSprite;
	sf::Texture			_backgroundTexture;
	sf::Sprite			_backgroundSprite;
	sf::Texture			_liveTexture;
	sf::Sprite			_liveSprite[MAX_LIVES];
	sf::Texture			_scoreBarTexture;
	sf::Sprite			_scoreBarSprite;
	sf::Texture			_gameOverTexture;
	sf::Sprite			_gameOverSprite;
	
	sf::Font			_font;
	sf::Text			_scoreText;
};

#endif // !GAME_H

