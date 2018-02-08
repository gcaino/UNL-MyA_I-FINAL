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

Los assets (mayormente las imágenes y algunos efectos de sonido) fueron tomados de los recursos provistos por el libro "Building JavaScript Games" del autor Arjan Egges, editorial Apress. Asimismo, la edición de las imágenes (para adaptarlas al proyecto) fue realizada por el alumno. 

En cuanto al código en general, si bien se realizó un gran esfuerzo para que sea lo más auto-explicativo posible (nombres de miembros de clase, formatos, convención, responsabilidad única de métodos, etc), se agregaron comentarios, puntualmente para enfatizar las partes en donde se implementaron funciones matemáticas o físicas vistas a lo largo de la cursada (MRU, MRUV, Trigonometría, etc). Los mismos se pueden visualizar en cada uno de los archivos .h

Por último, comentar que el desarrollo fue realizado bajo el paradigma de programación orientado a objetos, aunque se priorizó mantener la simplicidad en el árbol de clases, tanto a nivel de clases abstractas como utilización de interfaces, lo que derivó en un reducido pero cohesionado número de clases.



Repositorio en GitHub: https://github.com/gcaino/UNL-MyA_I-FINAL