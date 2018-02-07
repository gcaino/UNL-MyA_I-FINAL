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
	void updateScore();
	void decreaseLifeByOne();
	sf::RenderWindow* getWindow() { return _window; }

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void draw();

	void addSpriteToMousePointer();
	void loadTexturesAndSetSprites();
	void loadFontsAndSetTexts();
	void drawLives() const;
	void pause();
	void updateScoreBar();
	void updatePowerBar();
	void checkCollisions();
	void checkDefeatCondition();
	void checkIfStartAgain(sf::Event event);
	void checkIfBallLeftWindow();
	void reset();
	void checkIfPlay(sf::Event event);
	void checkIfStart(sf::Event event);
	
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 480;
	const int FPS = 60;
	const int SCORE_POINTS = 10;
	static const int MAX_LIVES = 5;

	enum STATE { MENU, INSTRUCTIONS, GAMEPLAY, PAUSE, GAMEOVER };
	STATE				 _currentState;

	sf::RenderWindow*	 _window;
	Cannon*				 _cannon;
	PaintBucketsManager* _paintBucketsManager;
	int					 _lives;
	int					 _score;
	bool				 _paused;

	sf::Texture			_crosshairTexture;
	sf::Sprite			_crosshairSprite;
	sf::Texture			_menuScreenTexture;
	sf::Sprite			_menuScreenSprite;
	sf::Texture			_instructionsTexture;
	sf::Sprite			_instructionsSprite;
	sf::Texture			_backgroundTexture;
	sf::Sprite			_backgroundSprite;
	sf::Texture			_liveTexture;
	sf::Sprite			_liveSprite[MAX_LIVES];
	sf::Texture			_barTexture;
	sf::Sprite			_scoreSpriteBar;
	sf::Sprite			_powerSpriteBar;
	sf::Texture			_gameOverTexture;
	sf::Sprite			_gameOverSprite;
	
	sf::Font			_font;
	sf::Text			_scoreText;
	sf::Text			_powerText;
};

#endif // !GAME_H

