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