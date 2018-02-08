#ifndef ENNUMS_H
#define ENNUMS_H
// ----------------------------------------------------------------------------
/**
* Espacio de nombre utilitario.
* Principalmente se utiliza para proveer un tipo que puedan compartir las distintas
* clases del juego.
* Es destacable la sobrecarga del operador de postincremento, el cual permite cambiar 
* el color del ca�on al incrementarse el �ndice de la enumeraci�n.
*/
// ----------------------------------------------------------------------------
namespace Utils
{
	enum COLORS { RED, BLUE, GREEN, TOTAL };

	COLORS& operator++(COLORS& original);
}
// ----------------------------------------------------------------------------
#endif // ENNUMS_H

