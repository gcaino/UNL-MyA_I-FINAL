#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	std::srand(static_cast<unsigned int>(time(NULL)));

	try
	{
		Game game;
		game.loop();
	}
	catch (const char* exception)
	{
		std::cerr << "Error: " << exception << std::endl;
	}

	return 0;
}