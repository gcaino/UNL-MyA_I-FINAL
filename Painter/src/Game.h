#ifndef GAME_H
#define GAME_H
// ----------------------------------------------------------------------------
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
// ----------------------------------------------------------------------------
class Cannon;
class PaintBucketsManager;
/**
* La clase Game provee la estructura general al juego, a partir del loop principal
* se realiza el llamado a los distintos métodos en función del estado o pantalla en
* la cual se encuentra el flujo del juego (Menú, Gameplay, etc).
* Es para destacar el control del 'Framerate', el cual hace posible que el juego 
* corra a la misma velocidad en las distintas máquinas. En tal sentido, el gameplay 
* es dependiente del tiempo transcurrido en cada frame (delta Time). Se multiplica 
* el incremento de los movimientos por el tiempo transcurrido.
* Por último, comentar el método 'checkCollision', el cual hace uso del método 'intersects'
* provisto por SFML para realizar un sencillo chequeo de colisiones entre dos rectángulos.
*/
// ----------------------------------------------------------------------------
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
	void loadSoundBuffersAndSetSounds();
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
	void checkIfLifeIncreases();
	
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;
	const int FPS = 60;
	const int SCORE_POINTS = 10;
	const int MAX_PAINT_BUCKETS = 3;
	static const int MAX_LIVES = 5;
	const int BASE_SCORE_POINTS_TO_GAIN_LIFE = 100;

	enum STATE { MENU, INSTRUCTIONS, GAMEPLAY, PAUSE, GAMEOVER };
	STATE				 _currentState;

	sf::RenderWindow*	 _window;
	Cannon*				 _cannon;
	PaintBucketsManager* _paintBucketsManager;
	int					 _lives;
	int					 _score;
	int					 _accumulatedScoreToGainLife;
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

	sf::SoundBuffer		_buttonClickSoundBuffer;
	sf::Sound			_buttonClickSound;
	sf::SoundBuffer		_bubblePopSoundBuffer;
	sf::Sound			_bubblePopSound;
	sf::SoundBuffer		_balloonExplodesSoundBuffer;
	sf::Sound			_balloonExplodesSound;
	sf::SoundBuffer		_gainLifeSoundBuffer;
	sf::Sound			_gainLifeSound;
	sf::Music			_music;
};
// ----------------------------------------------------------------------------
#endif // !GAME_H

