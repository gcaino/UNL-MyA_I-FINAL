- El juego fue desarrollado en Visual Studio 2017 Community y compilado con las siguientes opciones:
-- Configuration Properties: General: Windows SDK Version [Actual 8.1]
-- Configuration Properties: General: Platform Toolset [Actual Visual Studio 2015 (v140)]

* En caso de compilarlo en otra versión, tener en cuenta que de no cambiarse la configuración del proyecto puede arrojar errores, por lo que se deberán reconfigurar las opciones mencionadas anteriormente.

IMPORTANTE: debido a la limitación en el peso de subida del archivo (5 Mb), se decidió sacar la librería SFML del proyecto (50 Mb aproximádamente).
Para compilar la solución se deberán incluir en el proyecto, dentro de las carpetas:
- libs\SFML\lib\
- libs\SFML\include\
- libs\SFML\bin\

Los archivos contenidos en las carpetas de SFML con los mismos nombres, correspondientes a la versión: Visual C++ 14 (2015) - 32-bit
Link de descarga: https://www.sfml-dev.org/download/sfml/2.4.2/