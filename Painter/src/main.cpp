// ----------------------------------------------------------------------------
//	Materia: Modelos y Algoritmos I - TP FINAL
//	Autor: Germán Daniel Caíno
//	Versión: 1.0.0
//	Fecha: 15/01/2018
// ----------------------------------------------------------------------------
#include <iostream>
#include "Game.h"
// ----------------------------------------------------------------------------
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