#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
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