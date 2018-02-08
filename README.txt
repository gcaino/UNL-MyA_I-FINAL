- El juego fue desarrollado en Visual Studio 2017 Community y compilado con las siguientes opciones:
-- Configuration Properties: General: Windows SDK Version [Actual 8.1]
-- Configuration Properties: General: Platform Toolset [Actual Visual Studio 2015 (v140)]

* En caso de compilarlo en otra versi�n, tener en cuenta que de no cambiarse la configuraci�n del proyecto puede arrojar errores, por lo que se deber�n reconfigurar las opciones mencionadas anteriormente.

IMPORTANTE: debido a la limitaci�n en el peso de subida del archivo (5 Mb), se decidi� sacar la librer�a SFML del proyecto (50 Mb aproxim�damente).
Para compilar la soluci�n se deber�n incluir en el proyecto, dentro de las carpetas:
- libs\SFML\lib\
- libs\SFML\include\
- libs\SFML\bin\

Los archivos contenidos en las carpetas de SFML con los mismos nombres, correspondientes a la versi�n: Visual C++ 14 (2015) - 32-bit
Link de descarga: https://www.sfml-dev.org/download/sfml/2.4.2/

Los assets (mayormente las im�genes y algunos efectos de sonido) fueron tomados de los recursos provistos por el libro "Building JavaScript Games" del autor Arjan Egges, editorial Apress. Asimismo, la edici�n de las im�genes (para adaptarlas al proyecto) fue realizada por el alumno. 

En cuanto al c�digo en general, si bien se realiz� un gran esfuerzo para que sea lo m�s auto-explicativo posible (nombres de miembros de clase, formatos, convenci�n, responsabilidad �nica de m�todos, etc), se agregaron comentarios, puntualmente para enfatizar las partes en donde se implementaron funciones matem�ticas o f�sicas vistas a lo largo de la cursada (MRU, MRUV, Trigonometr�a, etc). Los mismos se pueden visualizar en cada uno de los archivos .h

Por �ltimo, comentar que el desarrollo fue realizado bajo el paradigma de programaci�n orientado a objetos, aunque se prioriz� mantener la simplicidad en el �rbol de clases, tanto a nivel de clases abstractas como utilizaci�n de interfaces, lo que deriv� en un reducido pero cohesionado n�mero de clases.



Repositorio en GitHub: https://github.com/gcaino/UNL-MyA_I-FINAL